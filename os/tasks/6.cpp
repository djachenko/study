#include <pthread.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstring>
#include <list>
#include <unistd.h>
#include <stdlib.h>

class PathPair
{
public:
	char from[256];
	char to[256];

	PathPair(char * a, char * b)
	{
		strncpy(from, a, 256);
		strncpy(to, b, 256);
	}

	PathPair(const PathPair & other, char * suffix)
	{
		sprintf(from, "%s/%s", other.from, suffix);
		sprintf(to, "%s/%s", other.to, suffix);
	}
};

std::list<pthread_t> threads;//global containers for deleting data in the end
std::list<PathPair *> pairs;
						
void * copyFile(void * x)
{
	PathPair *pair = (struct PathPair *)x;

	FILE * from = fopen(pair->from, "rb");

	while (NULL == from)
	{
		if (EMFILE == errno)
		{
			sleep(1);
			
			from = fopen(pair->from, "rb");
		}
		else
		{
			perror("Error while fopen");

			return NULL;
		}
	}

	FILE * to = fopen(pair->to, "wb");

	while (NULL == to)
	{
		if (EMFILE == errno)
		{
			sleep(1);
			
			to = fopen(pair->to, "wb");
		}
		else
		{
			perror("Error while fopen");
			fclose(from);

			return NULL;
		}
	}

	char buffer[1024];

	for (int readCount = 1024; readCount == 1024; )
	{
		readCount = fread(buffer, sizeof(*buffer), 1024, from);
		fwrite(buffer, sizeof(*buffer), readCount, to);
	}

	fclose(to);
	fclose(from);

	struct stat fileInfo;

	if (-1 == stat(pair->from, &fileInfo))
	{
		perror("Error while stat in copyFile");
	}
	else
	{
		if (-1 == chmod(pair->to, fileInfo.st_mode))
		{
			perror("Error while chmod");
		}
	}

	return NULL;
}

void * readDirectory(void * x)
{
	PathPair *pair = (PathPair *)x;

	struct stat dirInfo;

	if (-1 == stat(pair->from, &dirInfo))//value
	{
		perror("Error while stat");

		return NULL;
	}

	printf("%s %d %d %d %d\n", pair->from, S_ISDIR(dirInfo.st_mode), S_ISREG(dirInfo.st_mode), S_ISLNK(dirInfo.st_mode), S_ISFIFO(dirInfo.st_mode));

	if (S_ISREG(dirInfo.st_mode))
	{
		copyFile(pair);

		return NULL;
	}

	DIR * directory = opendir(pair->from);

	while (NULL == directory)
	{
		if (EMFILE == errno)
		{
			if (0 != sleep(1))
			{
				perror("Sleep was interrupted");
			}

			directory = opendir(pair->from);
		}
		else
		{
			perror("Error while opendir");

			return NULL;
		}
	}

	if (-1 == mkdir(pair->to, dirInfo.st_mode) && EEXIST != errno)
	{
		perror("Error while mkdir");
	}
	else
	{
		struct dirent *entryPtr = (struct dirent *)malloc(sizeof(*entryPtr) + pathconf(pair->from, _PC_NAME_MAX));

		for (bool flag = true; flag; )
		{
			struct dirent * temp = NULL;
			struct dirent ** checkPtr = &temp;

			if (0 != readdir_r(directory, entryPtr, checkPtr))
			{
				perror("Error while readdir_r");
				
				flag = false;
			}
			else if (NULL == *checkPtr)
			{
				flag = false;
			}
			else if (0 != strncmp(entryPtr->d_name, ".", 256) && 0 != strncmp(entryPtr->d_name, "..", 256))//prevent loop
			{
				PathPair * filePath = new PathPair(*pair, entryPtr->d_name);
				pthread_t thread;

				pairs.push_back(filePath);
				threads.push_back(thread);//copy

				struct stat entryInfo;

				if (-1 == stat(filePath->from, &entryInfo))//value
				{
					perror("Error while stat");
				}
				else if (S_ISDIR(entryInfo.st_mode) || S_ISREG(entryInfo.st_mode))
				{
					if (0 != pthread_create(&(threads.back()), NULL, readDirectory, filePath))
					{
						perror("Error while pthread_create");
					}
				}
			}
		}

		free(entryPtr);
	}
	
	if (-1 == closedir(directory))
	{
		perror("Error while closedir");
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	if (3 != argc)
	{
		perror("Wrong arguments' amount.\n");
	}
	else
	{
		if ('/' == argv[1][strlen(argv[1]) - 1])
		{
			argv[1][strlen(argv[1]) - 1] = 0;
		}

		if ('/' == argv[2][strlen(argv[2]) - 1])
		{
			argv[2][strlen(argv[2]) - 1] = 0;
		}

		PathPair * pair = new PathPair(argv[1], argv[2]);
		pthread_t thread;
							
		pairs.push_back(pair);
		threads.push_back(thread);

		if (0 != pthread_create(&(threads.back()), NULL, readDirectory, pair))
		{
			perror("Error while pthread_create.\n");
		}

		for ( ; !threads.empty(); )
		{
			int code = pthread_join(threads.front(), NULL);

			if (code != 0 && code != ESRCH)
			{
				perror("Error while pthread_join.\n");
			}

			threads.pop_front();

			delete pairs.front();
			pairs.pop_front();
		}
	}

	return 0;
}
