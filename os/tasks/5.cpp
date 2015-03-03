#include <cstdio>
#include <unistd.h>
#include <pthread.h>

void handler(void * parameter)
{
	printf("Thread was cancelled.\n");
}

void * threadFunction(void * parameter)
{
	pthread_cleanup_push(handler, NULL);

	for (int i = 0; ; i++)
	{
		printf("Line #%d\n", i);
	}

	pthread_cleanup_pop(0);

	return NULL;
}

int main()
{
	pthread_t thread;

	if (0 != pthread_create(&thread, NULL, threadFunction, NULL))
	{
		perror("Error while pthread_create.\n");
	}

	if (0 != sleep(2))
	{
		perror("Sleep was interrupted.\n");
	}

	if (0 != pthread_cancel(thread))
	{
		perror("Error while pthread_cancel.\n");
	}

	return 0;
}
