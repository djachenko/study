#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PHILO 4
#define DELAY 30000
#define FOOD 50

pthread_mutex_t foodLock;
pthread_mutex_t forkLock;

pthread_mutex_t forks[PHILO];
pthread_t philosophers[PHILO];

int sleep_seconds = 0;

struct parameter
{
	int id;
};

void get_fork(int phil, int fork, const char hand[])
{
	if (0 != pthread_mutex_lock(&forks[fork]))
	{
		perror("Error while pthread_mutex_lock() in get_fork().\n");
	}
	
	printf("Philosopher %d: got %s fork %d\n", phil, hand, fork);
}

void get_forks(int phil, int fork1, int fork2)
{
	if (0 != pthread_mutex_lock(&forkLock))
	{
		perror("Error while first pthread_mutex_lock() in get_forks().\n");
	}
	

	if (0 != pthread_mutex_lock(&forks[fork1]))
	{
		perror("Error while second pthread_mutex_lock() in get_forks().\n");
	}
	
	if (0 != pthread_mutex_lock(&forks[fork2]))
	{
		perror("Error while third pthread_mutex_lock() in get_forks().\n");
	}
	
	
	if (0 != pthread_mutex_unlock(&forkLock))
	{
		perror("Error while pthread_mutex_unlock() in get_forks().\n");
	}
}

void down_forks(int f1, int f2)
{
	if (0 != pthread_mutex_unlock(&forks[f1]))
	{
		perror("Error while pthread_mutex_unlock() in down_forks().\n");
	}
	
	if (0 != pthread_mutex_unlock(&forks[f2]))
	{
		perror("Error while pthread_mutex_unlock() in down_forks().\n");
	}
}

int food_on_table()
{
	static int food = FOOD;

	printf("%d\n", food);
	
	if (0 != pthread_mutex_lock(&foodLock))
	{
		perror("Error while third pthread_mutex_lock() in food_on_table().\n");
	}
	
	if(food > 0) 
	{
		food--;
	}
	
	int myfood = food;
	
	if (0 != pthread_mutex_unlock(&foodLock))
	{
		perror("Error while third pthread_mutex_lock() in food_on_table().\n");
	}
	
	return myfood;
}

void *philosopher(void *parameter)
{
	int f;

	int id = ((struct parameter *)parameter)->id;

	printf("Philosopher %d sitting down to dinner.\n", id);

	int left_fork = id % PHILO;
	int right_fork = (id + 1) % PHILO;

	while(0 != (f = food_on_table())) 
	{
		if(id == 1)
		{
			sleep(sleep_seconds);
		}

		printf("Philosopher %d: get dish %d.\n", id, f);
		
		get_fork(id, right_fork, "right");
		get_fork(id, left_fork, "left ");
/**/
//		get_forks(id, right_fork, left_fork);

		printf("Philosopher %d: eating.\n", id);
		
		usleep(DELAY * (FOOD - f + 1));
		down_forks(left_fork, right_fork);
	}
	
	printf("Philosopher %d is done eating.\n", id);
	
	return NULL;
}

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		sleep_seconds = atoi(argv[1]);
	}

	struct parameter *parameters = new struct parameter[PHILO];

	if (0 != pthread_mutex_init(&foodLock, NULL))
	{
		perror("Error while pthread_mutex_init(foodLock).\n");

	}
	
	if (0 != pthread_mutex_init(&forkLock, NULL))
	{
		perror("Error while pthread_mutex_init(forkLock).\n");
	}
	
	for(int i = 0; i < PHILO; i++)
	{
		if (0 != pthread_mutex_init(&forks[i], NULL))
		{
			perror("Error while pthread_mutex_init(forks).\n");
		}
	}

	for(int i = 0; i < PHILO; i++)
	{
		parameters[i].id = i;

		if (0 != pthread_create(&philosophers[i], NULL, philosopher, &parameters[i]))
		{
			perror("Error while pthread_create().\n");
		}
	}

	for(int i = 0; i < PHILO; i++)
	{
		if (0 != pthread_join(philosophers[i], NULL))
		{
			perror("Error while pthread_join().\n");
		}
	}
	
	for(int i = 0; i < PHILO; i++)
	{
		if (0 != pthread_mutex_destroy(&forks[i]))
		{
			perror("Error while pthread_mutex_destroy(forks).\n");
		}
	}

	if (0 != pthread_mutex_destroy(&forkLock))
	{
		perror("Error while pthread_mutex_destroy(forkLock).\n");
	}

	if (0 != pthread_mutex_destroy(&foodLock))
	{
		perror("Error while pthread_mutex_destroy(foodLock).\n");
	}

	delete[] parameters;

	return 0;
}
