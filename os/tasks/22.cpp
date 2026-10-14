#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdio>
#include <limits.h>

bool isStopped = false;

sem_t ASemaphore;
sem_t BSemaphore;
sem_t CSemaphore;

sem_t moduleSemaphore;

void * A(void * parameter)
{
	for ( ; !isStopped; )
	{
		sleep(1);

		sem_post(&ASemaphore);
	}

	return NULL;
}

void * B(void * parameter)
{
	for ( ; !isStopped; )
	{
		sleep(2);

		sem_post(&BSemaphore);
	}

	return NULL;
}

void * C(void * parameter)
{
	for ( ; !isStopped; )
	{
		sleep(3);

		sem_post(&CSemaphore);
	}

	return NULL;
}

void * module(void * parameter)
{
	for ( ; !isStopped; )
	{
		sem_wait(&ASemaphore);
		sem_wait(&BSemaphore);

		sem_post(&moduleSemaphore);
	}

	return NULL;
}

void * widget(void * parameter)
{
	int widgetCount = 0;

	for ( ; !isStopped; )
	{
		sem_wait(&CSemaphore);
		sem_wait(&moduleSemaphore);

		widgetCount++;

		printf("Widget %d produced\n", widgetCount);
	}

	return NULL;
}

void stop()
{
	isStopped = true;

	sem_post(&ASemaphore);
	sem_post(&BSemaphore);
	sem_post(&CSemaphore);
	sem_post(&moduleSemaphore);
}

int main()
{
	if (0 != sem_init(&ASemaphore, 0, 0))
	{
		perror("Error while sem_init with A.\n");
	}

	if (0 != sem_init(&BSemaphore, 0, 0))
	{
		perror("Error while sem_init with B.\n");
	}

	if (0 != sem_init(&CSemaphore, 0, 0))
	{
		perror("Error while sem_init with C.\n");
	}

	if (0 != sem_init(&moduleSemaphore, 0, 0))
	{
		perror("Error while sem_init with module.\n");
	}

	pthread_t AThread;
	pthread_t BThread;
	pthread_t CThread;
	pthread_t moduleThread;
	pthread_t widgetThread;

	printf("SEM_MAX: %d\n", _POSIX_SEM_VALUE_MAX);

	pthread_create(&AThread, NULL, A, NULL);
	pthread_create(&BThread, NULL, B, NULL);
	pthread_create(&CThread, NULL, C, NULL);
	pthread_create(&moduleThread, NULL, module, NULL);
	pthread_create(&widgetThread, NULL, widget, NULL);

	//input

	//stop();

	pthread_join(AThread, NULL);
	pthread_join(BThread, NULL);
	pthread_join(CThread, NULL);
	pthread_join(moduleThread, NULL);
	pthread_join(widgetThread, NULL);

	return 0;
}
