#include <cstdio>
#include <pthread.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>

void * threadFunction(void * parameter)
{
	char **sequences = (char **)parameter;

	for (int i = 0; i < 10; i++)
	{
		printf("%s", sequences[i]);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[4];

	char *** sequences = new char **[4];

	for (int i = 0; i < 4; i++)
	{
		sequences[i] = new char *[10];

		for (int j = 0; j < 10; j++)
		{
			sequences[i][j] = new char[25];
			memset(sequences[i][j], 0, 25 * sizeof(*sequences[i][j]));

			sprintf(sequences[i][j], "Line #%d in thread #%d\n", j, i);
		}

		if (0 != pthread_create(&threads[i], NULL, threadFunction, sequences[i]))
		{
			perror("Error while perror_create\n");
		}
	}

	for (int i = 0; i < 4; i++)
	{
		int code = pthread_join(threads[i], NULL);

		if (code != 0)
		{
			perror("Error while pthread_join.\n");

			if (ESRCH == code)
			{
				perror("Thread has already stopped.\n");
			}
		}

		for (int j = 0; j < 10; j++)
		{
			delete[] sequences[i][j];
		}

		delete[] sequences[i];
	}

	delete[] sequences;

	return 0;
}
