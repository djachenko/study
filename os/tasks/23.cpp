#include <pthread.h>
#include <semaphore.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

class Queue
{
private:
	class Entry
	{
	public:
		const static int BUFFERSIZE = 80;

		char * data;
		Entry * next;

		Entry(const char * msg, Entry *p = NULL)
		:data(new char[BUFFERSIZE + 1]), next(p)
		{
			if (NULL == msg)
			{
				delete[] data;//it's safe
				data = NULL;
			}
			else
			{
				strncpy(data, msg, BUFFERSIZE);
				data[BUFFERSIZE] = 0;
			}
		}

		~Entry()
		{
			delete[] data;
		}
	};

	Entry * head;
	Entry * tail;

	sem_t filledSlots;
	sem_t emptySlots;

	sem_t modificationSemaphore;

	bool isDropped;
public:
	const static int QUEUESIZE = 10;

	Queue()
	:head(NULL), tail(head), isDropped(false)
	{
		sem_init(&emptySlots, 0, QUEUESIZE);
		sem_init(&filledSlots, 0, 0);

		sem_init(&modificationSemaphore, 0, 1);
	}

	~Queue()
	{
		drop();

		for (Entry *i = head; i != NULL; )
		{
			Entry *p = i;
			i = i->next;

			delete p;
		}
	}

	void drop()
	{
		isDropped = true;

		sem_post(&filledSlots);
		sem_post(&emptySlots);

		sem_post(&modificationSemaphore);
	}

	int put(char * msg)
	{
		if (isDropped)
		{
			return 0;
		}

		sem_wait(&emptySlots);
		sem_wait(&modificationSemaphore);

		Entry * temp = new Entry(msg);

		if (NULL == tail)
		{
			head = temp;
		}
		else
		{
			tail->next = temp;
		}

		tail = temp;

		sem_post(&modificationSemaphore);
		sem_post(&filledSlots);

		if (isDropped)
		{
			return 0;
		}
		else
		{
			return strlen(temp->data);
		}
	}

	int get(char * buf, size_t bufsize)
	{
		if (isDropped)
		{
			return 0;
		}

		sem_wait(&filledSlots);
		sem_wait(&modificationSemaphore);

		Entry * temp = head;

		if (NULL == head->next)
		{
			tail = NULL;
		}

		head = head->next;

		sem_post(&modificationSemaphore);
		sem_post(&emptySlots);

		strncpy(buf, temp->data, bufsize);
		
		delete temp;
		
		if (isDropped)
		{
			sem_post(&modificationSemaphore);
			memset(buf, 0, bufsize);

			return 0;
		}
		else
		{
			return strlen(buf);
		}
	}
};

struct Parameter
{
	Queue * queue;
	int id;
};

void * producer(void * parameter)
{
	Queue * queue = ((struct Parameter *)parameter)->queue;
	int id = ((struct Parameter *)parameter)->id;

	char * message = new char[255];

	for (int i = 0; i < 1024; i++)
	{
		sprintf(message, "Line number %d from producer %d", i, id);

		queue->put(message);

		printf("%s\n", message);
	}

	delete[] message;

	return NULL;
}

void * consumer(void * parameter)
{
	Queue * queue = ((struct Parameter *)parameter)->queue;
	int id = ((struct Parameter *)parameter)->id;

	char * message = new char[256];

	for (int i = 0; i < 1024; i++)
	{
		queue->get(message, 256);

		sleep(1);

		printf("%s read by consumer %d\n", message, id);
	}

	delete[] message;

	return NULL;
}

int main()
{
	Queue queue;

	pthread_t producers[2];
	struct Parameter producerParameters[2];

	pthread_t consumers[2];
	struct Parameter consumerParameters[2];

	for (int i = 0; i < 2; i++)
	{
		producerParameters[i].id = i;
		producerParameters[i].queue = &queue;
		
		pthread_create(&producers[i], NULL, producer, &producerParameters[i]);
	} 

	for (int i = 0; i < 2; i++)
	{
		consumerParameters[i].id = i;
		consumerParameters[i].queue = &queue;
		
		pthread_create(&consumers[i], NULL, consumer, &consumerParameters[i]);
	} 


	for (int i = 0; i < 2; i++)
	{
		pthread_join(producers[i], NULL);
	} 

	for (int i = 0; i < 2; i++)
	{
		pthread_join(consumers[i], NULL);
	} 

	return 0;
}
