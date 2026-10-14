#include <cstdio>
#include <pthread.h>

void * threadFunction(void * p)
{
	int x = *(int *)p;

	int i;

	for (i = 0; i < 10; i++)
	{
		printf("Line #%d from thread %d\n", i, x);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t thread;

	int b = 0;

	if (0 != pthread_create(&thread, NULL, threadFunction, &b))
	{
		perror("Error while perror_create.\n");
	}
	else
	{
		int a = 1;

		threadFunction(&a);
	}

	return 0;
}
