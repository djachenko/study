#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstdlib>
#include <aio.h>

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

	printf("name: \'%s\'\n", hostName);

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

	char * buffers[2];
	buffers[0] = new char[BUFFERSIZE];
	buffers[1] = new char[BUFFERSIZE];

	sprintf(buffers[0], pattern, url);

	if (-1 == send(httpSocket, buffers[0], strlen(buffers[0]), 0))
	{
		perror("Error while send(command)");

		exit(EXIT_FAILURE);
	}

//=========================================================================================

	struct aiocb aioSocket;
	memset(&aioSocket, 0, sizeof(aioSocket));
	aioSocket.aio_fildes = httpSocket;
	aioSocket.aio_buf = buffers[1];
	aioSocket.aio_nbytes = BUFFERSIZE;

	struct aiocb * aioQueue[1];

	aioQueue[0] = &aioSocket;

	int linesWritten = 0;

	bool allowedToStop = false;

	if (0 != aio_read(&aioSocket))
	{
		perror("Error while initial aio_read()");

		exit(EXIT_FAILURE);
	}

	for (int iteration = 0; !allowedToStop; iteration++)
	{
		if (-1 == aio_suspend(aioQueue, 1, NULL))
		{
			perror("Error while aio_suspend()");

			exit(EXIT_FAILURE);
		}

		int end = aio_return(&aioSocket);
		int start = 0;

		if (0 == end)
		{
			allowedToStop = true;
		}
		else if (end > 0)
		{
			aioSocket.aio_buf = buffers[iteration % 2];
			aio_read(&aioSocket);

			char * current = buffers[(iteration + 1) % 2];

			while (start < end)
			{
				char * enter = strchr(current + start, '\n');

				int lineEnd;

				if (NULL == enter)
				{
					lineEnd = end;
				}
				else
				{
					lineEnd = enter - current + 1;
				}

				int written = write(STDIN_FILENO, current + start, lineEnd - start);

				if (-1 == written)
				{
					perror("Error while write().\n");

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

				if (linesWritten == 25)
				{
					char temp[8];

					if (-1 == read(STDIN_FILENO, temp, sizeof(temp)))
					{
						perror("Error while reading from terminal");
					}

					linesWritten = 0;
				}
			}

			memset(current, 0, end);
		}
		else
		{
			perror("Error while aio_return");

			exit(EXIT_FAILURE);
		}
	}

	delete[] buffers[0];
	delete[] buffers[1];
	delete[] hostName;

	putchar('\n');

	return 0;
}
