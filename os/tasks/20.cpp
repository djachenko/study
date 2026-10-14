#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define THREADCOUNT 3
#define BUFFERSIZE 81

bool isStopped = false;

class LinkedList
{
public:
	class List
	{
	public:
		char * data;
		List * next;

		pthread_rwlock_t rwlock;

		List(const char *str, List *previousHead)
		:data(strdup(str)), next(previousHead)
		{
			pthread_rwlock_init(&rwlock, NULL);
		}

		~List()
		{
			//delete[] data;
			free(data);

			pthread_rwlock_destroy(&rwlock);
		}

		void rdlock()
		{
			pthread_rwlock_rdlock(&rwlock);
		}

		void wrlock()
		{
			pthread_rwlock_wrlock(&rwlock);
		}

		void unlock()
		{
			pthread_rwlock_unlock(&rwlock);
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
		head->wrlock();

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
		previous->rdlock();
  
		for (List * p = head->next; p != NULL; p = p->next, i++)
		{
			p->rdlock();

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

	for ( ; !isStopped; )
	{
		sleep(delay);

		for (bool repeatNeeded = true; repeatNeeded; )
		{
			repeatNeeded = false;

			bool sleepNeeded = false;

			for (LinkedList::List *previous = list->head; ; previous = previous->next)
			{
				previous->rdlock();

				LinkedList::List *current = previous->next;

				if (NULL == current)
				{
					previous->unlock();

					break;
				}
				else
				{
					current->rdlock();//current != NULL, check on previous step
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
					postCurrent->rdlock();
				}

				if (strcmp(current->data, postCurrent->data) > 0)
				{
					previous->unlock();
					current->unlock();
					postCurrent->unlock();

					previous->wrlock();
					current->wrlock();
					postCurrent->wrlock();

					if (strcmp(current->data, postCurrent->data) > 0)
					{
						previous->next = postCurrent;
						current->next = postCurrent->next;
						postCurrent->next = current;

						repeatNeeded = true;
						sleepNeeded = true;
					}
				}

				previous->unlock();
				current->unlock();
				postCurrent->unlock();

				if (sleepNeeded)
				{
					sleep(1);
				}
			}
		}
	}

	return NULL;
}

int main()
{
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

	isStopped = true;

	for (int i = 0; i < THREADCOUNT; i++)
	{
		pthread_join(threads[i], NULL);
	}

	return 0;
}
