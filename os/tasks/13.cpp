#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
#include <semaphore.h>

class Parameter
{
public:
	sem_t * currentSemaphore;
	sem_t * otherSemaphore;
	char *name;

	Parameter(const char * str)
	:name(new char[strlen(str) + 1])
	{
		strncpy(name, str, strlen(str));
	}

	~Parameter()
	{
		delete[] name;
	}
};

void * threadFunction(void * parameter)
{
	Parameter *properties = (Parameter *)parameter;

	for (int i = 0; i < 10; i++)
	{
		sem_wait(properties->currentSemaphore);

		printf("Line %d from thread %s\n", i, properties->name);
		
		sem_post(properties->otherSemaphore);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t thread;

	sem_t childSemaphore;
	sem_t parentSemaphore;

	sem_init(&childSemaphore, 0, 1);
	sem_init(&parentSemaphore, 0, 0);

	Parameter childParameter("child");
	childParameter.currentSemaphore = &childSemaphore;
	childParameter.otherSemaphore = &parentSemaphore;

	if (0 != pthread_create(&thread, NULL, threadFunction, &childParameter))
	{
		perror("Error while perror_create.\n");
	}
	else
	{
		Parameter parentParameter("parent");
		parentParameter.currentSemaphore = &parentSemaphore;
		parentParameter.otherSemaphore = &childSemaphore;

		threadFunction(&parentParameter);
		
		if (0 != pthread_join(thread, NULL))
		{
			perror("Error while pthread_join.\n");
		}
	}

	sem_destroy(&childSemaphore);
	sem_destroy(&parentSemaphore);

	return 0;
}
