#include <pthread.h>
#include <cstdio>
#include <cstdlib>

struct parameter
{
	int number;
	int index;
};

void * pi(void * parameter)
{
	int iterations = 1000000;
	double sum = 0;

	int number = ((struct parameter *)parameter)->number;
	int index = ((struct parameter *)parameter)->index;

	int sign;
	int signStep;

	if (0 == index % 2)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}

	if (0 == number % 2)
	{
		signStep = 1;
	}
	else
	{
		signStep = -1;
	}

	for (int i = 0; i < iterations; i++)
	{
		sum += 1.0 / (2 * (number * i + index) + 1) * sign;

		sign *= signStep;
	}

	double * result = new double;

	*result = sum;

	return result;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		perror("Wrong number of arguments.\n");
	}
	else
	{
		int threadNumber = atoi(argv[1]);

		pthread_t *threads = new pthread_t[threadNumber];
		struct parameter *parameters = new struct parameter[threadNumber];

		for (int i = 0; i < threadNumber; i++)
		{
			parameters[i].number = threadNumber;
			parameters[i].index = i;

			if (0 != pthread_create(&threads[i], NULL, pi, &parameters[i]))
			{
				perror("Error while pthread_create.\n");
			}
		}

		double sum = 0;

		for (int i = 0; i < threadNumber; i++)
		{
			void * partSum;

			if (0 != pthread_join(threads[i], &partSum))
			{
				perror("Error while pthread_join.\n");
			}

			sum += *(double *)partSum;

			delete (double *)partSum;
		}

		sum *= 4;

		printf("%lf\n", sum);

		delete[] parameters;
		delete[] threads;
	}

	return 0;
}
