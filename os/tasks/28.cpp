#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>

#define DEFAULTPORT 80
#define BUFFERSIZE (16 * 1024)

struct Buffer
{
	char * buffers[2];
	int ends[2];

	sem_t full;
	sem_t empty;

	int socket;
};

bool finished = false;

void * writeThread(void * p)
{
	struct Buffer * parameter = (struct Buffer *)p;

	int id = 0;
	int linesWritten = 0;

	while (!finished || parameter->ends[id] != 0)
	{
		sem_wait(&(parameter->full));

		char * buffer = parameter->buffers[id];
		int localEnd = parameter->ends[id];

		for (int localStart = 0; localStart < localEnd; )
		{
			char * enter = strchr(buffer + localStart, '\n');

			int lineEnd;

			if (NULL == enter)
			{
				lineEnd = localEnd;
			}
			else
			{
				lineEnd = enter - buffer + 1;
			}

			int written = write(STDIN_FILENO, buffer + localStart, lineEnd - localStart);

			if (-1 == written)
			{
				perror("Error while write()");

				exit(EXIT_FAILURE);
			}
			else
			{
				localStart += written;

				if (localStart == lineEnd && NULL != enter)
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

		memset(buffer, 0, localEnd);
		parameter->ends[id] = 0;

		id = (id + 1) % 2;

		sem_post(&(parameter->empty));
	}

	return NULL;
}

void * readThread(void * p)
{
	struct Buffer * parameter = (struct Buffer *)p;
	int socket = parameter->socket;

	int id = 1;

	for (int i = 0; !finished; i++)
	{
		sem_wait(&(parameter->empty));

		id = (id + 1) % 2;

		char * buffer = parameter->buffers[id];

		int localEnd = 0;

		while (!finished && localEnd < BUFFERSIZE)
		{
			int wasRead = recv(socket, buffer + localEnd, BUFFERSIZE - localEnd, 0);

			switch (wasRead)
			{
				case -1:
					perror("Error while read()");

					exit(EXIT_FAILURE);
				case 0:
					finished = true;

					break;
				default:
					localEnd += wasRead;

					break;
			}
		}

		parameter->ends[id] = localEnd;

		sem_post(&(parameter->full));
	}

	return NULL;
}

int main(int argc, char *argv[])
{
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

	struct Buffer parameter;
	parameter.buffers[0] = new char[BUFFERSIZE];
	parameter.buffers[1] = new char[BUFFERSIZE];

	sprintf(parameter.buffers[0], pattern, url);

	if (-1 == send(httpSocket, parameter.buffers[0], strlen(parameter.buffers[0]), 0))
	{
		perror("Error while send(command)");

		exit(EXIT_FAILURE);
	}

//=========================================================================================

	parameter.ends[0] = 0;
	parameter.ends[1] = 0;

	sem_init(&parameter.empty, 0, 2);
	sem_init(&parameter.full, 0, 0);

	parameter.socket = httpSocket;

	pthread_t thread;

	pthread_create(&thread, NULL, writeThread, &parameter);

	readThread(&parameter);

	pthread_join(thread, NULL);

	close(httpSocket);

	delete[] parameter.buffers[0];
	delete[] parameter.buffers[1];

	putchar('\n');

	return 0;
}
