#include <pthread.h>
#include <semaphore.h>
#include <cstring>
#include <cstdio>

#define SINGLE

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

	int size;

	pthread_mutex_t modificationMutex;
	pthread_cond_t modificationCond;

	bool isDropped;
public:
	const static int QUEUESIZE = 10;

	Queue()
	:head(NULL), tail(head), size(0), isDropped(false)
	{
		pthread_mutex_init(&modificationMutex, NULL);
		pthread_cond_init(&modificationCond, NULL);
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

		pthread_mutex_destroy(&modificationMutex);
		pthread_cond_destroy(&modificationCond);
	}

	void drop()
	{
		isDropped = true;

		pthread_mutex_lock(&modificationMutex);
		pthread_cond_broadcast(&modificationCond);
		pthread_mutex_unlock(&modificationMutex);
	}

	int put(char * msg)
	{
		if (isDropped)
		{
			return 0;
		}

		pthread_mutex_lock(&modificationMutex);
		
		while (size >= QUEUESIZE && !isDropped)
		{
			pthread_cond_wait(&modificationCond, &modificationMutex);
		}

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

		size++;

		pthread_cond_signal(&modificationCond);

		pthread_mutex_unlock(&modificationMutex);

		if (isDropped)
		{
			return strlen(temp->data);
		}
		else
		{
			return 0;
		}
	}

	int get(char * buf, size_t bufsize)
	{
		if (isDropped)
		{
			return 0;
		}

		pthread_mutex_lock(&modificationMutex);

		while (size <= 0 && !isDropped)
		{
			pthread_cond_wait(&modificationCond, &modificationMutex);
		}

		if (!isDropped)
		{
			Entry * temp = head;

			if (NULL == head->next)
			{
				tail = NULL;
			}

			head = head->next;

			size--;

			pthread_cond_signal(&modificationCond);

			pthread_mutex_unlock(&modificationMutex);

			strncpy(buf, temp->data, bufsize);
		
			delete temp;

			return strlen(buf);
		}
		else
		{
			return 0;
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

	for (int i = 0; i < 10; i++)
	{
		sprintf(message, "Line number %d from producer %d", i, id);

		queue->put(message);
	}

	delete[] message;

	return NULL;
}

void * consumer(void * parameter)
{
	Queue * queue = ((struct Parameter *)parameter)->queue;
	int id = ((struct Parameter *)parameter)->id;

	char * message = new char[256];

	for (int i = 0; i < 10; i++)
	{
		queue->get(message, 256);

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
