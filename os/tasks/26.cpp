#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#include <cstdlib>

#define DEFAULTPORT 80
#define BUFFERSIZE (16 * 1024)

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("Wrong amount of arguments.\n");

		exit(EXIT_FAILURE);
	}

	char * url = argv[1];//just for readability

	char * protocolEnd = strstr(url, "://");

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

//=====================================================================

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

//========================================================================================

	char pattern[] = "GET %s HTTP/1.0\n\n\0";
	char * buffer = new char[BUFFERSIZE];

	sprintf(buffer, pattern, url);

	if (-1 == send(httpSocket, buffer, strlen(buffer), 0))
	{
		perror("Error while send(command)");

		exit(EXIT_FAILURE);
	}

//=========================================================================================

	struct pollfd * pollfds = new struct pollfd[3];

	pollfds[0].fd = httpSocket;//to server
	pollfds[0].events = POLLIN;

	pollfds[1].fd = -1; //STDOUT
	pollfds[1].events = POLLOUT;

	pollfds[2].fd = -1;//STDIN 
	pollfds[2].events = POLLIN;

	int linesWritten = 0;
	int start = 0;
	int end = 0;

	bool finishedReading = false;
	bool allowedToStop = false;

	while (!allowedToStop)
	{
		int ready = poll(pollfds, 3, -1);

		if (-1 == ready)
		{
			perror("Error while poll()");

			exit(EXIT_FAILURE);
		}
		else if (0 == ready)
		{
			continue;
		}

		if (0 != (pollfds[1].revents & POLLOUT) && end > start && linesWritten < 25)
		{
			char * enter = strchr(buffer + start, '\n');

			int lineEnd;

			if (NULL == enter)
			{
				lineEnd = end;
			}
			else
			{
				lineEnd = enter - buffer + 1;
			}

			int written = write(pollfds[1].fd, buffer + start, lineEnd - start);

			if (-1 == written)
			{
				perror("Error while write()");

				exit(EXIT_FAILURE);
			}
			else
			{
				start += written;

				if (start == lineEnd && enter != NULL)
				{
					linesWritten++;
				}
			}

			if (start == end)
			{
				memset(buffer, 0, end);

				start = 0;
				end = 0;

				pollfds[0].fd = httpSocket;

				if (finishedReading)
				{
					allowedToStop = true;
				}
			}
				
			if (linesWritten == 25)
			{
				pollfds[1].fd = -1;
				pollfds[2].fd = STDIN_FILENO;
			}
		}
		
		if (0 != (pollfds[0].revents & POLLIN) && BUFFERSIZE - end > 0)
		{
			int wasRead = recv(pollfds[0].fd, buffer + end, BUFFERSIZE - end, 0);

			switch(wasRead)
			{
				case -1:
					perror("Error while read().\n");

					exit(EXIT_FAILURE);
				case 0:
					close(pollfds[0].fd);
					pollfds[0].fd = -1;

					finishedReading = true;

					break;
				default:
					end += wasRead;
					pollfds[1].fd = STDOUT_FILENO;

					if (BUFFERSIZE == end)
					{
						pollfds[0].fd = -1;
					}

					break;
			}
		}

		if (0 != (pollfds[2].revents & POLLIN) && linesWritten >= 25)
		{
			char temp[8];

			if (-1 == read(pollfds[2].fd, temp, sizeof(temp)))
			{
				perror("Error whil reading from terminal");
			}

			linesWritten = 0;
			pollfds[1].fd = STDOUT_FILENO;
			pollfds[2].fd = -1;
		}
	}

	delete[] pollfds;
	delete[] buffer;
	delete[] hostName;

	putchar('\n');

	return 0;
}
