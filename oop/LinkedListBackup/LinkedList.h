#include <iostream>
#include <cstdlib>

using namespace std;

#ifndef LinkedList_h
#define LinkedList_h

template <typename T>
class LinkedList
{
	private:
		struct List
		{
			T value;
			struct List * previous;
			struct List * next;
		};

		struct List * head;
		struct List * tail;
	public:
		class Iterator
		{
			friend class LinkedList;
			private:
				List * pointer;
			public:
				Iterator();
				Iterator(const Iterator & other);
				~Iterator();

				Iterator & operator=(const Iterator & other);
				Iterator & operator=(struct List * other);

				bool operator!=(const Iterator & other) const;
				bool operator==(const Iterator & other) const;

				T & operator*() const;
				T * operator->() const;

				Iterator operator++();
				Iterator & operator++(int);
				Iterator operator--();
				Iterator & operator--(int);

				void print();
		};

		LinkedList();
		LinkedList(const LinkedList & other);
		~LinkedList();

		T & front();
		const T & front() const;
		T & back();
		const T & back() const;

		Iterator begin() const;//needed for access from other methods
		Iterator end() const;

		bool contains(const T & value) const;
		int count(const T & value) const;
		int size() const;
		bool empty() const;

		Iterator erase(Iterator & pos);
		Iterator erase(Iterator begin, Iterator end);

		void clear();
		int removeAll(const T & value);
		bool removeOne(const T & value);

		void push_front(const T & value);
		void push_back(const T & value);
		T pop_front();
		T pop_back();

		Iterator insert(Iterator before, const T & value);

		bool operator!=(const LinkedList & other) const;//test!
		bool operator==(const LinkedList & other) const;
		LinkedList operator+(const LinkedList & other) const;//test!
		LinkedList & operator+=(const LinkedList & other);
		LinkedList & operator+=(const T & value);
		LinkedList & operator=(const LinkedList & other);

		void print();
	private:
		Iterator first;
		Iterator last;
};

//<Iterator>

template <typename T>
LinkedList<T>::Iterator::Iterator()
:pointer(NULL)
{
}

template <typename T>
LinkedList<T>::Iterator::Iterator(const Iterator & other)
:pointer(other.pointer)
{
}

template <typename T>
LinkedList<T>::Iterator::~Iterator()
{
}

template <typename T>
typename LinkedList<T>::Iterator & LinkedList<T>::Iterator::operator=(const Iterator & other)
{
	this->pointer = other.pointer;

	return *this;
}

template <typename T>
typename LinkedList<T>::Iterator & LinkedList<T>::Iterator::operator=(struct List * other)
{
	this->pointer = other;

	return *this;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator & other) const
{
	return !(*this == other);
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator & other) const
{
	return this->pointer == other.pointer;
}

template <typename T>
T & LinkedList<T>::Iterator::operator*() const
{
	return this->pointer->value;
}

template <typename T>
T * LinkedList<T>::Iterator::operator->() const
{
	return &(this->pointer->value);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++()
{
	Iterator temp = *this;

	this->pointer = this->pointer->next;

	return temp;
}

template <typename T>
typename LinkedList<T>::Iterator & LinkedList<T>::Iterator::operator++(int)
{
	this->pointer = this->pointer->next;

	return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--()
{
	Iterator temp = *this;

	this->pointer = this->pointer->previous;

	return temp;
}

template <typename T>
typename LinkedList<T>::Iterator & LinkedList<T>::Iterator::operator--(int)
{
	this->pointer = this->pointer->previous;

	return *this;
}

template <typename T>
void LinkedList<T>::Iterator::print()
{
	cout << "pointer: " << this->pointer << endl;
	cout << "value: " << this->pointer->value << endl;
	cout << "prev: " << this->pointer->previous << endl;
	cout << "next: " << this->pointer->next << endl;
	cout << endl;
}

//</Iterator>

template <typename T>
LinkedList<T>::LinkedList()
:head(NULL), tail(NULL)
{
	first = head;
	last = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList & other)
:head(NULL), tail(NULL)
{
	first = head;
	last = NULL;

	(*this)+=other;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	this->clear();
}

template <typename T>
T & LinkedList<T>::front()
{
	return this->head->value;
}

template <typename T>
const T & LinkedList<T>::front() const
{
	return this->head->value;
}

template <typename T>
T & LinkedList<T>::back()
{
	return this->tail->value;
}

template <typename T>
const T & LinkedList<T>::back() const
{
	return this->tail->value;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const
{
	return first;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() const
{
	return last;
}

template <typename T>
bool LinkedList<T>::contains(const T & value) const
{
	for (typename LinkedList<T>::Iterator i = this->begin(); i != this->end(); i++)
	{
		if (*i == value)
		{
			return true;
		}
	}

	return false;
}

template <typename T>
int LinkedList<T>::count(const T & value) const
{
	int result = 0;

	for (typename LinkedList<T>::Iterator i = this->begin(); i != this->end(); i++)
	{
		if (*i == value)
		{
			result++;
		}
	}

	return result;
}

template <typename T>
int LinkedList<T>::size() const
{
	int result = 0;

	for (typename LinkedList<T>::Iterator i = this->begin(); i != this->end(); i++)
	{
		result++;
	}

	return result;
}

template <typename T>
bool LinkedList<T>::empty() const
{
	return NULL != this->head;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::erase(Iterator & pos)
{
	struct List * temp = pos.pointer;
	pos++;

	if (temp == this->head)
	{
		this->head = temp->next;

		this->first = this->head;
	}
	else
	{
		temp->previous->next = temp->next;//not head
	}

	if (temp == this->tail)
	{
		this->tail = temp->previous;
	}
	else
	{
		temp->next->previous = temp->previous;//not tail
	}

	delete temp;

	return pos;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::erase(Iterator begin, Iterator end)
{
	for (typename LinkedList<T>::Iterator i = begin; i != end;)
	{
		this->erase(i);
	}

	return end;
}

template <typename T>
void LinkedList<T>::clear()
{
	erase(this->begin(), this->end());
}

template <typename T>
int LinkedList<T>::removeAll(const T & value)
{
	int count=0;

	for (typename LinkedList<T>::Iterator i = this->begin(); i != this->end();)
	{
		if (*i == value)
		{
			this->erase(i);

			count++;
		}
		else
		{
			i++;
		}
	}

	return count;
}

template <typename T>
bool LinkedList<T>::removeOne(const T & value)
{
	for (typename LinkedList<T>::Iterator i = this->begin(); i != this->end(); )
	{
		if (*i == value)
		{
			this->erase(i);

			return true;
		}
		else
		{
			i++;
		}
	}

	return false;
}

template <typename T>
void LinkedList<T>::print()
{
	cout << "PRINT\n";

	cout << "head: " << (int)head << '\n';

	if (head)
	{
		cout << "value: " << (int)head->value << '\n';
		cout << "next: " << (int)head->next << '\n';
		cout << "prev: " << (int)head->previous << '\n';
	}

	cout << "tail: " << (int)tail << '\n';

	if (tail)
	{
		cout << "value: " << (int)tail->value << '\n';
		cout << "next: " << (int)tail->next << '\n';
		cout << "prev: " << (int)tail->previous << '\n';
	}
}

template <typename T>
void LinkedList<T>::push_front(const T & value)
{
	struct List * a = new struct List;
	a->value = value;

	if (NULL == this->head)
	{
		tail = a;
	}
	else
	{
		this->head->previous = a;
	}

	a->previous = NULL;
	a->next = head;
	head = a;

	first = head;
}

template <typename T>
void LinkedList<T>::push_back(const T & value)
{
	struct List * a = new struct List;
	a->value = value;

	a->next = NULL;

	if (NULL == this->head)
	{
		head = a;
		first = head;
	}
	else
	{
		this->tail->next = a;
		a->previous = tail;
	}

	tail=a;
}

template <typename T>
T LinkedList<T>::pop_front()
{
	T result = this->head->value;

	struct List * temp = this->head;

	this->head = this->head->next;

	first = this->head;

	if (NULL == this->head)
	{
		this->tail = NULL;
	}

	delete temp;

	return result;
}

template <typename T>
T LinkedList<T>::pop_back()
{
	T result = this->tail->value;

	struct List * temp = this->tail;

	this->tail = this->tail->previous;

	if (NULL == this->tail)
	{
		this->head = NULL;

		first = this->head;
	}

	delete temp;

	return result;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::insert(Iterator before, const T & value)
{
	struct List * ins = new struct List;

	ins->value = value;

	if (before.pointer == this->head)
	{
		head = ins;
		first = head;
		ins->previous = NULL;
	}
	else
	{
		(before.pointer->previous)->next = ins;
		ins->previous = before.pointer->previous;
	}

	before.pointer->previous = ins;
	ins->next = before.pointer;

	return before;
}

template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<T> & other) const
{
	typename LinkedList<T>::Iterator i;
	typename LinkedList<T>::Iterator j;

	for (i = this->begin(), j = other.begin(); i != this->end() || j != other.end(); i++, j++)
	{
		if (*i != *j)
		{
			return true;
		}
	}

	return false;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> & other) const
{
	return !(*this != other);
}

template <typename T>
LinkedList<T> LinkedList<T>::operator+(const LinkedList<T> & other) const
{
	LinkedList<T> result;

	result+=*this;
	result+=other;

	return result;
}

template <typename T>
LinkedList<T> & LinkedList<T>::operator+=(const LinkedList<T> & other)
{
	for (typename LinkedList<T>::Iterator i = other.begin(); i != other.end(); i++)
	{
		this->push_back(*i);
	}

	return *this;
}

template <typename T>
LinkedList<T> & LinkedList<T>::operator+=(const T & value)
{
	this->push_back(value);

	return *this;
}

template <typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & other)
{
	this->clear();

	(*this) += other;//???

	return *this;
}

#endif
