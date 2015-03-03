#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define THREADCOUNT 5
#define BUFFERSIZE 81

bool isStopped = false;
pthread_mutex_t flagMutex;

class LinkedList
{
public:
	class List
	{
	public:
		char * data;
		List * next;

		pthread_mutex_t mutex;

		List(const char *str, List *previousHead)
		:data(strdup(str)), next(previousHead)
		{
			pthread_mutex_init(&mutex, NULL);
		}

		~List()
		{
			//delete[] data;
			free(data);

			pthread_mutex_destroy(&mutex);
		}

		void lock()
		{
			pthread_mutex_lock(&mutex);
		}

		void unlock()
		{
			pthread_mutex_unlock(&mutex);
		}
	};

	List * head;

	LinkedList()
	:head(new List("\0", NULL))
	{
	}

	~LinkedList()
	{
		List * p = head;

		while (p != NULL)
		{
			List * q = p;
			p = p->next;

			delete q;
		}
	}

	void push_front(char *str)
	{
		head->lock();

		head->next = new List(str, head->next);

		head->unlock();
	}

	void print()
	{
		int i = 0;

		/*
		modification point mustn't overtake output point
		so two locks in order of having lock at every quant of time
		*/

		List * previous = head;
		previous->lock();
  
		for (List * p = head->next; p != NULL; p = p->next, i++)
		{
			p->lock();

			printf("%d: %s\n", i, p->data);

			previous->unlock();
			
			previous = p;
		}

		previous->unlock();
	}
};

struct Parameter
{
	int delay;
	LinkedList *list;
};

void * sort(void * parameter)
{
	int delay = ((struct Parameter *)parameter)->delay;

	LinkedList *list = ((struct Parameter *)parameter)->list;

	for (bool localFlag = false; !localFlag; )
	{
		pthread_mutex_lock(&flagMutex);

		localFlag = isStopped;

		pthread_mutex_unlock(&flagMutex);

		sleep(delay);

		for (bool repeatNeeded = true; repeatNeeded; )
		{
			repeatNeeded = false;

			for (LinkedList::List *previous = list->head; ; previous = previous->next)
			{
				previous->lock();

				LinkedList::List *current = previous->next;

				if (NULL == current)
				{
					previous->unlock();

					break;
				}
				else
				{
					current->lock();
				}

				LinkedList::List *postCurrent = current->next;

				if (NULL == postCurrent)
				{
					previous->unlock();
					current->unlock();

					break;
				}
				else
				{
					postCurrent->lock();
				}

				if (strcmp(current->data, postCurrent->data) > 0)
				{
					previous->next = postCurrent;
					current->next = postCurrent->next;
					postCurrent->next = current;

					repeatNeeded = true;
				}

				previous->unlock();
				current->unlock();
				postCurrent->unlock();
			}
		}
	}

	return NULL;
}

int main()
{
	pthread_mutex_init(&flagMutex, NULL);

	LinkedList list;

	struct Parameter params[THREADCOUNT];
	pthread_t threads[THREADCOUNT];

	for (int i = 0; i < THREADCOUNT; i++)
	{
		params[i].delay = (i + 1) * 5;
		params[i].list = &list;

		pthread_create(&threads[i], NULL, sort, &params[i]);
	}

	char buffer[BUFFERSIZE] = {0};

	bool isEndOfString = true;

	printf("> ");

	while (NULL != fgets(buffer, sizeof(buffer), stdin) && 0 != strcmp(buffer, "stop\n"))
	{
		char * p = strchr(buffer, '\n');

		if (NULL == p)
		{
			isEndOfString = false;
		}
		else
		{
			*p = 0;
		}

		if (0 == strlen(buffer))
		{
			if (isEndOfString)
			{
				list.print();
			}
		}
		else
		{
			list.push_front(buffer);
		}

		if (NULL != p)
		{
			isEndOfString = true;

			printf("> ");
		}
	}

	pthread_mutex_lock(&flagMutex);

	isStopped = true;

	pthread_mutex_unlock(&flagMutex);

	for (int i = 0; i < THREADCOUNT; i++)
	{
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&flagMutex);

	return 0;
}
