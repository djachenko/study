#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

class Parameter
{
public:
	bool *currentFlag;
	bool *otherFlag;
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

pthread_mutex_t mainMutex;
pthread_cond_t cond;

void * threadFunction(void * parameter)
{
	Parameter *properties = (Parameter *)parameter;

	for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mainMutex);

		while (!*(properties->currentFlag))
		{
			pthread_cond_wait(&cond, &mainMutex);
		}

		printf("Line %d from thread %s\n", i, properties->name);
		*(properties->currentFlag) = false;
		*(properties->otherFlag) = true;
		
		pthread_cond_signal(&cond);
		
		pthread_mutex_unlock(&mainMutex);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t thread;

	bool childFlag = true;
	bool parentFlag = !childFlag;

	Parameter childParameter("child");
	childParameter.currentFlag = &childFlag;
	childParameter.otherFlag = &parentFlag;

	if (0 != pthread_create(&thread, NULL, threadFunction, &childParameter))
	{
		perror("Error while perror_create");
	}
	else
	{
		Parameter parentParameter("parent");
		parentParameter.currentFlag = &parentFlag;
		parentParameter.otherFlag = &childFlag;

		threadFunction(&parentParameter);
		
		if (0 != pthread_join(thread, NULL))
		{
			perror("Error while pthread_join");
		}
	}

	return 0;
}
