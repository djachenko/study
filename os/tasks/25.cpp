#include <cstdlib>//exit, atoi
#include <cstdio>//perror
#include <netdb.h>//gethostbyname
#include <cstring>//memcpy
#include <sys/socket.h>//sockaddr_in, AF_INET, socket, bind, listen, connect
#include <poll.h>//poll
#include <unistd.h>//read, write, close
#include <arpa/inet.h>//htonl, htons

#define SOCKETCOUNT (1 + 510 * 2)
//1 for serverSocket and 510 pairs for connections
#define BUFFERSIZE (4096)

struct attr
{
	char buffer[BUFFERSIZE];
	int start;
	int end;
};

int main(int argc, char *argv[])
{
	if (4 != argc)
	{
		perror("Wrong number of arguments.\n");

		exit(EXIT_FAILURE);
	}

	int serverPort = atoi(argv[1]);
	int remotePort = atoi(argv[3]);

	if (0 == serverPort)
	{
		perror("Wrong port for listening.\n");

		exit(EXIT_FAILURE);
	}

	struct hostent * hostInfo = gethostbyname(argv[2]);

	if (NULL == hostInfo)
	{
		perror("Error while gethostbyname.\n");

		exit(EXIT_FAILURE);
	}

	struct sockaddr_in destinationAddress;

	destinationAddress.sin_family = AF_INET;
	destinationAddress.sin_port = htons(remotePort);
	memcpy(&destinationAddress.sin_addr, hostInfo->h_addr, hostInfo->h_length);

//======================================================================================

	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (-1 == serverSocket)
	{
		perror("Error while creating serverSocket.\n");

		exit(EXIT_FAILURE);
	}

	struct sockaddr_in serverAddress;

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(serverPort);

	if (-1 == bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
	{
		perror("Error while binding.\n");

		exit(EXIT_FAILURE);
	}

	if (-1 == listen(serverSocket, 1024))
	{
		perror("Error while listen().\n");

		exit(EXIT_FAILURE);
	}

//======================================================================================

	struct pollfd *sockets = new struct pollfd[SOCKETCOUNT];
	struct attr *attrs = new struct attr[SOCKETCOUNT];//one odd

	for (int i = 0; i < SOCKETCOUNT; i++)
	{
		sockets[i].fd = -1;
		sockets[i].events = 0;

		attrs[i].start = 0;
		attrs[i].end = 0;
	}

	sockets[0].fd = serverSocket;
	sockets[0].events = POLLIN;

	int connectionCount = 0;
	int max = 0;
	int count = 0;

	for ( ; ; )
	{
		int readyCount = poll(sockets, SOCKETCOUNT, -1);

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

			if (connectionCount < 510)
			{
				int outcomingSocket = socket(PF_INET, SOCK_STREAM, 0);

				if (-1 == outcomingSocket)
				{
					perror("Error while creating outcoming socket.\n");

					exit(EXIT_FAILURE);
				}

				if (-1 == connect(outcomingSocket, (struct sockaddr *)&destinationAddress, sizeof(destinationAddress)))
				{
					perror("Error while connecting to remote.\n");

					exit(EXIT_FAILURE);
				}

				bool foundEmptySlot = false;

				for (int j = 1; j < SOCKETCOUNT && !foundEmptySlot; j += 2)
				{
					if (-1 == sockets[j].fd)
					{
						foundEmptySlot = true;

						sockets[j].fd = incomingSocket;
						sockets[j + 1].fd = outcomingSocket;

						sockets[j].events = POLLIN;
						sockets[j + 1].events = POLLIN;

						attrs[j].start = 0;
						attrs[j].end = 0;

						attrs[j + 1].start = 0;
						attrs[j + 1].end = 0;

						connectionCount++;
						count++;

						if (connectionCount > max)
						{
							max = connectionCount;
						}

						printf("+ %d %d %d\n", connectionCount, max, count);
					}
				}
			}
			else
			{
				close(incomingSocket);
			}

			readyCount--;
		}

		for (int i = 1; i < SOCKETCOUNT && readyCount > 0; i++)
		{
			int other;

			if (1 == i % 2)
			{
				other = i + 1;
			}
			else
			{
				other = i - 1;
			}

			if (0 != (sockets[i].revents & POLLIN))
			{
			 	if (BUFFERSIZE != attrs[i].end)//second - read only to empty buffer
			 	{
					int received = read(sockets[i].fd, attrs[i].buffer + attrs[i].end, BUFFERSIZE - attrs[i].end);

					switch (received)
					{
						case -1:
							perror("Error while read()");
							printf("conn: %d\n", i);

							exit(EXIT_FAILURE);

						case 0:
							close(sockets[i].fd);
							sockets[i].fd = -1;
							sockets[i].events = 0;
							
							if (0 == attrs[i].end)
							{
								close(sockets[other].fd);
								sockets[other].fd = -1;
								sockets[other].events = 0;

								connectionCount--;

								printf("- %d\n", connectionCount);
							}

							break;

						default:
							attrs[i].end += received;

							if (BUFFERSIZE == attrs[i].end)
							{
								sockets[i].events = sockets[i].events & (~ POLLIN);
							}
							
							sockets[other].events = sockets[other].events | POLLOUT;

							break;
					}
			 	}

				readyCount--;
			}
			else if (0 != (sockets[i].revents & POLLOUT))
			{
				if (0 != attrs[other].end)
				{
					int written = send(sockets[i].fd, attrs[other].buffer + attrs[other].start, attrs[other].end - attrs[other].start, 0);

					switch (written)
					{
						case -1:
							perror("Error while write()");
							printf("conn %d\n", i);

							exit(EXIT_FAILURE);

						case 0:
							close(sockets[i].fd);
							sockets[i].fd = -1;
							sockets[i].events = 0;

							if (0 == attrs[i].end)
							{
								close(sockets[other].fd);
								sockets[other].fd = -1;
								sockets[other].events = 0;

								connectionCount--;

								printf("- %d\n", connectionCount);
							}

							break;
	
						default:
							attrs[other].start += written;

							if (attrs[other].start == attrs[other].end)
							{
								if (-1 == sockets[other].fd)
								{
									close(sockets[i].fd);
									sockets[i].fd = -1;
									sockets[i].events = 0;

									connectionCount--;

									printf("- %d\n", connectionCount);
								}
								else
								{
									attrs[other].start = 0;
									attrs[other].end = 0;

									sockets[i].events = sockets[i].events & (~ POLLOUT);
									sockets[other].events = sockets[other].events | POLLIN;
								}
							}
					}
				}
				else if (-1 == sockets[other].fd)//stash, read=0
				{
					close(sockets[i].fd);
					sockets[i].fd = -1;
					sockets[i].events = 0;

					connectionCount--;

					printf("- %d\n", connectionCount);
				}

				readyCount--;
			}
			else if (0 != (sockets[i].revents & POLLHUP))
			{
				exit(0);
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
