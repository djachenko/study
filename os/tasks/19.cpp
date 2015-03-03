#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

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

		List(char *str, List *previousHead)
		:data(strdup(str)), next(previousHead)
		{
		}

		~List()
		{
			//delete[] data;
			free(data);			 
		}
	};

	List * head;
	pthread_rwlock_t rwlock;

	LinkedList()
	:head(NULL)
	{
		pthread_rwlock_init(&rwlock, NULL);
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

		pthread_rwlock_destroy(&rwlock);
	}

	void push_front(char *str)
	{
		wrlock();

		head = new List(str, head);

		unlock();
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

	void print()
	{
		rdlock();

		int i = 0;

		for (List * p = head; p != NULL; p = p->next, i++)
		{
			printf("%d: %s\n", i, p->data);
		}

		unlock();
	}
};

void * sort(void * parameter)
{
	LinkedList *list = (LinkedList *)parameter;

	for (bool localFlag = false; !localFlag; )
	{
		pthread_mutex_lock(&flagMutex);

		localFlag = isStopped;

		pthread_mutex_unlock(&flagMutex);

		sleep(5);

		list->rdlock();

		for (bool flag = true; flag; )
		{
			flag = false;

			LinkedList::List *previous = NULL;

			for (LinkedList::List *i =list->head; i->next != NULL; )
			{
				if (strcmp(i->data, i->next->data) > 0)
				{
					list->unlock();
					list->wrlock();

					if (strcmp(i->data, i->next->data) > 0)
					{
						if (NULL != previous)
						{
							previous->next = i->next;
						}
						else
						{
							list->head = i->next;
						}

						previous = i->next;
						i->next = i->next->next;
						previous->next = i;

						flag = true;
					}

					list->unlock();
					list->rdlock();
				}
				else
				{
					previous = i;

					i = i->next;
				}
			}
		}

		list->unlock();
	}

	return NULL;
}

int main()
{
	pthread_mutex_init(&flagMutex, NULL);

	LinkedList list;

	pthread_t thread;

	pthread_create(&thread, NULL, sort, &list);

	char buffer[BUFFERSIZE] = {0};

	bool flag = true;

	printf("> ");

	while (NULL != fgets(buffer, sizeof(buffer), stdin) && 0 != strcmp(buffer, "stop\n"))
	{
		char * p = strchr(buffer, '\n');

		if (NULL == p)
		{
			flag = false;
		}
		else
		{
			*p = 0;
		}

		if (0 == strlen(buffer))
		{
			if (flag)
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
			flag = true;

			printf("> ");
		}
	}

	pthread_mutex_lock(&flagMutex);

	isStopped = true;
	
	pthread_mutex_unlock(&flagMutex);

	pthread_join(thread, NULL);

	pthread_mutex_destroy(&flagMutex);

	return 0;
}
