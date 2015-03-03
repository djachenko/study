#include <cstdlib>//exit, atoi
#include <cstdio>//perror
#include <netdb.h>//gethostbyname
#include <cstring>//memcpy
#include <sys/socket.h>//sockaddr_in, AF_INET, socket, bind, listen, connect
#include <poll.h>//poll
#include <unistd.h>//read, write, close
#include <arpa/inet.h>//htonl, htons

#define INCOMINGNUMBER 512
#define OUTCOMINGNUMBER 512
#define SOCKETNUMBER (1 + INCOMINGNUMBER + OUTCOMINGNUMBER)//1 for serverSocket and 510 pairs for connections
#define STARTBUFFERSIZE (4096)

struct InAttr
{
	char *buffer;

	int start;
	int end;

	int size;
};

struct OutAttr
{
	char *buffer;

	int start;
	int end;

	int size;
};

int parsePort(char *arg)
{
	int serverPort = atoi(arg);

	if (0 == serverPort)
	{
		perror("Wrong port for listening.\n");

		exit(EXIT_FAILURE);
	}

	return serverPort;
}

int listeningSocket(int serverPort)
{
	int socket = socket(PF_INET, SOCK_STREAM, 0);

	if (-1 == socket)
	{
		perror("Error while creating serverSocket.\n");

		exit(EXIT_FAILURE);
	}

	struct sockaddr_in serverAddress;

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(serverPort);

	if (-1 == bind(socket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
	{
		perror("Error while binding.\n");

		exit(EXIT_FAILURE);
	}

	if (-1 == listen(socket, 1024))
	{
		perror("Error while listen().\n");

		exit(EXIT_FAILURE);
	}

	return socket;
}

int acceptConnection(int serverSocket, struct pollfd *incoming, struct InAttr *inAttrs, int &incomingCount)
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
	inAttrs[incomingCount].buffer = malloc(STARTBUFFERSIZE * sizeof(*(inAttrs[incomingCount].buffer)));

	memset(inAttrs[incomingCount].buffer, 0, inAttrs[incomingCount].size);

	incomingCount++;

	return incomingSocket;
}

int connectToRemote(const char *buffer, int length)
{
	char *temp = new char[length + 1];
	strncpy(temp, buffer, length);
	temp[length];

	char *method = strtok(temp, " ");
	char *uri = strtok(NULL, " ");
	char *version = strtok(NULL, "\n\0");

	char * protocolEnd = strstr(uri, "://");
	char *hostEnd = strchr(protocolEnd + 3, '/');

	int hostLength = 0;

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

	return httpSocket;
}

int main(int argc, char *argv[])
{
	if (4 != argc)
	{
		perror("Wrong number of arguments.\n");

		exit(EXIT_FAILURE);
	}

	int serverPort = parsePort(argv[1]);

//======================================================================================

	int serverSocket = listeningSocket(serverPort);

//======================================================================================

	struct pollfd *sockets = new struct pollfd[SOCKETNUMBER];

	struct pollfd *incoming = sockets + 1;
	int incomingCount = 0;

	struct pollfd *outcoming = incoming + INCOMINGNUMBER;
	int outcomingCount = 0;

	struct InAttr *inAttrs = new struct InAttr[INCOMINGNUMBER];
	struct OutAttr *outAttrs = new struct OutAttr[OUTCOMINGNUMBER]

	for (int i = 0; i < SOCKETNUMBER; i++)
	{
		sockets[i].fd = -1;
		sockets[i].events = 0;
	}

	sockets[0].fd = serverSocket;
	sockets[0].events = POLLIN;

	int connectionCount = 0;
	int max = 0;
	int count = 0;

	for ( ; ; )
	{
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
			int incomingSocket = acceptConnection(serverSocket, incoming, inAttrs, incomingCount);

			readyCount--;
		}

		for (int i = 0; i < INCOMINGNUMBER && readyCount > 0; i++)
		{
			if (0 != (incoming[i].revents & POLLIN))
			{
				int received = read(incoming[i].fd, inAttrs[i].buffer + inAttrs[i].end, BUFFERSIZE - inAttrs[i].end);

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

							char * result = realloc(inAttrs[i].buffer, inAttrs[i].size);

							if (NULL == result)
							{
								exit(EXIT_FAILURE);
							}
							else
							{
								inAttrs[i].buffer = result;
							}
						}

						char * enter = strchr(inAttrs[i].buffer, '\n');

						if (enter != NULL)
						{
							int httpSocket = connectToRemote(inAttrs[i].buffer, enter - inAttrs[i].buffer);

							outcoming[outcomingCount].fd = httpSocket;
							outcoming[outcomingCount].events = POLLOUT;

							outcomingCount++;
						}

						break;
				}

				readyCount--;
			}
			else if (0 != (incoming[i].revents & POLLOUT))
			{
				int written = send(incoming[i].fd, outAttrs[i].buffer + outAttrs[i].start, outAttrs[i].end - outAttrs[i].start, 0);

				switch (written)
				{
					case -1:
						perror("Error while write().\n");

						exit(EXIT_FAILURE);

					case 0:
						close(incoming[i].fd);
						incoming[i].fd = -1;

						break;

					default:
						outAttrs[i].start += written;

						if (outAttrs[i].start == outAttrs[i].end)
						{
							close(incoming[i].fd);
							incoming[i].fd = -1;
						}
				}
			}
		}

		for (int i = 0; i < OUTCOMINGNUMBER; i++)
		{
			if (0 != (outcoming[i].revents | POLLIN))
			{
				int received = recv(outcoming[i].fd, outAttrs[i].buffer + outAttrs[i].end, outAttrs[i].size - outAttrs[i].end, 0);

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

						if (outAttrs[i].end == outAttrs[i].size)
						{
							outAttrs[i].size *= 2;
							void * result = realloc(outAttrs[i].buffer, outAttrs[i].size);
						}
				}
			}
			else if (0 != (outcoming[i].revents | POLLOUT))
			{

			}
		}
		if (connectionCount >= 510)
		{
			sockets[0].fd = -1;
		}
		else
		{
			sockets[0].fd = serverSocket;
		}
	}

	close(serverSocket);

	delete[] attrs;
	delete[] sockets;
//	freehostent(hostInfo);

//	freeaddrinfo(&destinationAddrInfo);

	return 0;
}
