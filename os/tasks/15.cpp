#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
#include <semaphore.h>
#include <fcntl.h>

class Parameter
{
public:
	sem_t * currentSemaphore;
	sem_t * otherSemaphore;
	char *name;

	Parameter(const char * str)
	:name(strdup(str))
	{
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
	sem_t *childSemaphore = sem_open("/child", O_CREAT, 775, 1);
	sem_t *parentSemaphore = sem_open("/parent", O_CREAT, 775, 0);

	Parameter *parameter;

	int forkRes = fork();

	if (0 == forkRes)
	{
		parameter = new Parameter("child");
		parameter->currentSemaphore = childSemaphore;
		parameter->otherSemaphore = parentSemaphore;
	}
	else
	{
		parameter = new Parameter("parent");
		parameter->currentSemaphore = parentSemaphore;
		parameter->otherSemaphore = childSemaphore;
	}

	threadFunction(parameter);

	delete parameter;

	sem_close(childSemaphore);
	sem_close(parentSemaphore);

	if (0 != forkRes)
	{
		sem_unlink("/child");
		sem_unlink("/parent");
	}

	return 0;
}
