#include <cstdlib>//exit, atoi
#include <cstdio>//perror
#include <netdb.h>//gethostbyname
#include <cstring>//memcpy
#include <sys/socket.h>//sockaddr_in, AF_INET, socket, bind, listen, connect
#include <poll.h>//poll
#include <unistd.h>//read, write, close
#include <arpa/inet.h>//htonl, htons

#include <map>
#include <string>

#define INCOMINGNUMBER 510
#define OUTCOMINGNUMBER 510
#define SOCKETNUMBER (1 + INCOMINGNUMBER + OUTCOMINGNUMBER)//1 for serverSocket and 510 pairs for connections
#define STARTBUFFERSIZE (4096)
#define DEFAULTPORT 80

struct InAttr
{
	char *buffer;

	int start;
	int end;

	int pageStart;

	int size;

	int pageID;
};

struct Page
{
	char * buffer;
	int size;
}

struct OutAttr
{
	struct Page page;

	int end;
};

int main(int argc, char *argv[])
{
	if (2 != argc)
	{
		perror("Wrong number of arguments.\n");

		exit(EXIT_FAILURE);
	}

	int serverPort = atoi(argv[1]);

	if (0 == serverPort)
	{
		perror("Wrong port for listening.\n");

		exit(EXIT_FAILURE);
	}

//======================================================================================

	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (-1 == serverSocket)
	{
		perror("Error while creating serverSocket.\n");

		exit(EXIT_FAILURE);
	}

	{
		struct sockaddr_in serverAddress;

		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
		serverAddress.sin_port = htons(serverPort);

		if (-1 == (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress))))
		{
			perror("Error while binding.\n");

			exit(EXIT_FAILURE);
		}

		if (-1 == listen(serverSocket, 1024))
		{
			perror("Error while listen().\n");

			exit(EXIT_FAILURE);
		}
	}

//======================================================================================

	struct pollfd *sockets = new struct pollfd[SOCKETNUMBER];

	struct pollfd *incoming = sockets + 1;
	int incomingCount = 0;

	struct pollfd *outcoming = incoming + INCOMINGNUMBER;
	int outcomingCount = 0;

	struct InAttr *inAttrs = new struct InAttr[INCOMINGNUMBER];
	struct OutAttr *outAttrs = new struct OutAttr[OUTCOMINGNUMBER];

	std::map<std::string, char *> cache;

	for (int i = 0; i < SOCKETNUMBER; i++)
	{
		sockets[i].fd = -1;
		sockets[i].events = 0;
	}

	sockets[0].fd = serverSocket;
	sockets[0].events = POLLIN;

	for ( ; ; )
	{
		printf("poll %d %d\n", sockets, SOCKETNUMBER);

		int readyCount = poll(sockets, SOCKETNUMBER, -1);

		if (-1 == readyCount)
		{
			perror("Error while poll().\n");

			exit(EXIT_FAILURE);
		}
		else if (0 == readyCount)
		{
			perror("poll() returned 0.\n");

			continue;
		}

		if (0 != (sockets[0].revents & POLLIN))
		{
			struct sockaddr_in incomingAddress;
			int incomingAddressLength = sizeof(incomingAddress);

			int incomingSocket = accept(serverSocket, (struct sockaddr *)&incomingAddress, (socklen_t *)&incomingAddressLength);

			if (-1 == incomingSocket)
			{
				perror("Error while accept().\n");

				exit(EXIT_FAILURE);
			}

			incoming[incomingCount].fd = incomingSocket;
			incoming[incomingCount].events = POLLIN;

			inAttrs[incomingCount].start = 0;
			inAttrs[incomingCount].end = 0;
			inAttrs[incomingCount].size = STARTBUFFERSIZE;
			inAttrs[incomingCount].buffer = (char *)malloc(inAttrs[incomingCount].size * sizeof(*(inAttrs[incomingCount].buffer)));

			memset(inAttrs[incomingCount].buffer, 0, inAttrs[incomingCount].size);

			incomingCount++;

			readyCount--;
		}

		for (int i = 0; i < INCOMINGNUMBER && readyCount > 0; i++)
		{
			if (0 != (incoming[i].revents & POLLIN))
			{
				int received = recv(incoming[i].fd, inAttrs[i].buffer + inAttrs[i].end, inAttrs[i].size - inAttrs[i].end, 0);

				switch (received)
				{
					case -1:
						perror("Error while read().\n");

						exit(EXIT_FAILURE);

					case 0:
						close(incoming[i].fd);
						incoming[i].fd = -1;

						break;

					default:
						inAttrs[i].end += received;

						if (inAttrs[i].end == inAttrs[i].size)
						{
							inAttrs[i].size *= 2;

							char * result = (char *)realloc(inAttrs[i].buffer, inAttrs[i].size);

							if (NULL == result)
							{
								perror("Error while incoming realloc.\n");

								exit(EXIT_FAILURE);
							}
							else
							{
								inAttrs[i].buffer = result;
							}
						}

						printf("in %s\n", inAttrs[i].buffer);

						char * enter = strchr(inAttrs[i].buffer, '\n');

						if (enter != NULL)
						{
							int requestLength = enter - inAttrs[i].buffer;

							char * request = new char[requestLength + 1];
							strncpy(request, inAttrs[i].buffer, requestLength);
							request[requestLength] = 0;

							if (cache.find(request) == cache.end())
							{
								char *method = strtok(request, " ");
								char *uri = strtok(NULL, " ");
								char *version = strtok(NULL, "\n\0");

								printf("method: %s\n", method);
								printf("uri: %s\n", uri);
								printf("version: %s\n", version);

								char * protocolEnd = strstr(uri, "://");

								if (NULL == protocolEnd)
								{
									perror("Wrong protocol.\n");

									exit(EXIT_FAILURE);
								}

								char *hostEnd = strchr(protocolEnd + 3, '/');

								int hostLength = 0;

								printf("ok\n");

								if (NULL == hostEnd)
								{
									hostLength = strlen(protocolEnd + 3);
								}
								else
								{
									hostLength = hostEnd - (protocolEnd + 3);
								}

								char * hostName = new char[hostLength + 1];
								strncpy(hostName, protocolEnd + 3, hostLength);
								hostName[hostLength] = 0;

								printf("hostName: %s\n", hostName);

								struct hostent * hostInfo = gethostbyname(hostName);

								if (NULL == hostInfo)
								{
									perror("Error while gethostbyname.\n");

									exit(EXIT_FAILURE);
								}

								struct sockaddr_in destinationAddress;

								destinationAddress.sin_family = AF_INET;
								destinationAddress.sin_port = htons(DEFAULTPORT);
								memcpy(&destinationAddress.sin_addr, hostInfo->h_addr, hostInfo->h_length);

								int httpSocket = socket(AF_INET, SOCK_STREAM, 0);

								if (-1 == httpSocket)
								{
									perror("Error while socket().\n");

									exit(EXIT_FAILURE);
								}

								if (-1 == connect(httpSocket, (struct sockaddr *)&destinationAddress, sizeof(destinationAddress)))
								{
									perror("Error while connect().\n");

									exit(EXIT_FAILURE);
								}

								outcoming[outcomingCount].fd = httpSocket;
								inAttrs[i].pageID = outcomingCount;
								outcomingCount++;
							}

//								freehostent(hostInfo);
							delete[] request;
						}

						outcoming[inAttrs[i].pageID].events |= POLLOUT;

						break;
				}

				readyCount--;
			}
			else if (0 != (incoming[i].revents & POLLOUT))
			{
				int id = inAttrs[i].pageID;

				int sent = send(incoming[i].fd, outAttrs[id].buffer + inAttrs[i].pageStart, outAttrs[id].end - inAttrs[i].pageStart, 0);

				switch (sent)
				{
					case -1:
						perror("Error while write().\n");

						exit(EXIT_FAILURE);

					case 0:
						close(incoming[i].fd);
						incoming[i].fd = -1;

						break;

					default:
						inAttrs[i].pageStart += sent;

						if (inAttrs[i].pageStart == outAttrs[id].end)
						{
							incoming[i].events &= ~POLLOUT;
						}
				}
			}
		}

		for (int i = 0; i < OUTCOMINGNUMBER; i++)
		{
			if (0 != (outcoming[i].revents & POLLIN))
			{
				int received = recv(outcoming[i].fd, outAttrs[i].page.buffer + outAttrs[i].end, outAttrs[i].page.size - outAttrs[i].end, 0);

				switch (received)
				{
					case -1:
						perror("Error while recv(outcoming).\n");

						exit(EXIT_FAILURE);
					case 0:
						close(outcoming[i].fd);
						outcoming[i].fd = -1;

						break;

					default:
						outAttrs[i].end += received;

						if (outAttrs[i].end == outAttrs[i].page.size)
						{
							outAttrs[i].page.size *= 2;

							char * result = (char *)realloc(outAttrs[i].page.buffer, outAttrs[i].page.size);

							if (NULL == result)
							{
								perror("Error while outcoming realloc.\n");

								exit(EXIT_FAILURE);
							}
							else
							{
								outAttrs[i].page.buffer = result;
							}
						}

						//incoming[i].events |= POLLOUT;
				}
			}
			else if (0 != (outcoming[i].revents & POLLOUT))
			{
				int sent = send(outcoming[i].fd, inAttrs[i].buffer, inAttrs[i].end - inAttrs[i].start, 0);

				switch (sent)
				{
					case -1:
						perror("Error while send(outcoming).\n");

						break;
					case 0:
						close(outcoming[i].fd);
						outcoming[i].fd = -1;

						break;
					default:
						inAttrs[i].start += sent;

						if (inAttrs[i].start == inAttrs[i].end)
						{
							outcoming[i].events &= ~POLLOUT;
						}
				}
			}
		}
	}

	close(serverSocket);

	delete[] inAttrs;
	delete[] outAttrs;
	delete[] sockets;

	return 0;
}


























