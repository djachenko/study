#include <iostream>
#include <cstdlib>
#include "LinkedList.h"

using namespace std;

//<Iterator>

template <typename value_type>
LinkedList<value_type>::Iterator::Iterator()
:pointer(NULL)
{
}

template <typename value_type>
LinkedList<value_type>::Iterator::Iterator(const Iterator & other)
:pointer(other.pointer)
{
}

template <typename value_type>
LinkedList<value_type>::Iterator::~Iterator()
{
}

template <typename value_type>
LinkedList<value_type>::Iterator & LinkedList<value_type>::Iterator::operator=(const Iterator & other)
{
	this->pointer = other.pointer;

	return *this;
}

template <typename value_type>
LinkedList<value_type>::Iterator & LinkedList<value_type>::Iterator::operator=(struct List * other)
{
	this->pointer = other;

	return *this;
}

template <typename value_type>
bool LinkedList<value_type>::Iterator::operator!=(const Iterator & other) const
{
	return !(*this == other);
}

template <typename value_type>
bool LinkedList<value_type>::Iterator::operator==(const Iterator & other) const
{
	return this->pointer == other.pointer;
}

template <typename value_type>
value_type & LinkedList<value_type>::Iterator::operator*() const
{
	return this->pointer->value;
}

template <typename value_type>
value_type * LinkedList<value_type>::Iterator::operator->() const
{
	return &(this->pointer->value);
}

template <typename value_type>
LinkedList<value_type>::Iterator LinkedList<value_type>::Iterator::operator++()
{
	Iterator temp = *this;

	this->pointer = this->pointer->next;

	return temp;
}

template <typename value_type>
LinkedList<value_type>::Iterator & LinkedList<value_type>::Iterator::operator++(int)
{
	this->pointer = this->pointer->next;

	return *this;
}

template <typename value_type>
LinkedList<value_type>::Iterator LinkedList<value_type>::Iterator::operator--()
{
	Iterator temp = *this;

	this->pointer = this->pointer->previous;

	return temp;
}

template <typename value_type>
LinkedList<value_type>::Iterator & LinkedList<value_type>::Iterator::operator--(int)
{
	this->pointer = this->pointer->previous;

	return *this;
}

template <typename value_type>
void LinkedList<value_type>::Iterator::print()
{
	cout << "pointer: " << this->pointer << endl;
	cout << "value: " << this->pointer->value << endl;
	cout << "prev: " << this->pointer->previous << endl;
	cout << "next: " << this->pointer->next << endl;
	cout << endl;
}

//</Iterator>

template <typename value_type>
LinkedList<value_type>::LinkedList()
:head(NULL), tail(NULL)
{
	first = head;
	last = NULL;
}

template <typename value_type>
LinkedList<value_type>::LinkedList(const LinkedList & other)
:head(NULL), tail(NULL)
{
	first = head;
	last = NULL;

	(*this)+=other;
}

template <typename value_type>
LinkedList<value_type>::~LinkedList()
{
	this->clear();
}

template <typename value_type>
value_type & LinkedList<value_type>::front()
{
	return this->head->value;
}

template <typename value_type>
const value_type & LinkedList<value_type>::front() const
{
	return this->head->value;
}

template <typename value_type>
value_type & LinkedList<value_type>::back()
{
	return this->tail->value;
}

template <typename value_type>
const value_type & LinkedList<value_type>::back() const
{
	return this->tail->value;
}

template <typename value_type>
LinkedList<value_type>::Iterator LinkedList<value_type>::begin() const
{
	return first;
}

template <typename value_type>
LinkedList<value_type>::Iterator LinkedList<value_type>::end() const
{
	return last;
}

template <typename value_type>
bool LinkedList<value_type>::contains(const value_type & value) const
{
	for (LinkedList<value_type>::Iterator i = this->begin(); i != this->end(); i++)
	{
		if (*i == value)
		{
			return true;
		}
	}

	return false;
}

template <typename value_type>
int LinkedList<value_type>::count(const value_type & value) const
{
	int result = 0;

	for (LinkedList<value_type>::Iterator i = this->begin(); i != this->end(); i++)
	{
		if (*i == value)
		{
			result++;
		}
	}

	return result;
}

template <typename value_type>
int LinkedList<value_type>::size() const
{
	int result = 0;

	for (LinkedList<value_type>::Iterator i = this->begin(); i != this->end(); i++)
	{
		result++;
	}

	return result;
}

template <typename value_type>
bool LinkedList<value_type>::empty() const
{
	return NULL != this->head;
}

template <typename value_type>
LinkedList<value_type>::Iterator LinkedList<value_type>::erase(Iterator & pos)
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

template <typename value_type>
LinkedList<value_type>::Iterator LinkedList<value_type>::erase(Iterator begin, Iterator end)
{
	for (LinkedList<value_type>::Iterator i = begin; i != end;)
	{
		this->erase(i);
	}

	return end;
}

template <typename value_type>
void LinkedList<value_type>::clear()
{
	erase(this->begin(), this->end());
}

template <typename value_type>
int LinkedList<value_type>::removeAll(const value_type & value)
{
	int count=0;

	for (LinkedList<value_type>::Iterator i = this->begin(); i != this->end();)
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

template <typename value_type>
bool LinkedList<value_type>::removeOne(const value_type & value)
{
	for (LinkedList<value_type>::Iterator i = this->begin(); i != this->end(); )
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

template <typename value_type>
void LinkedList<value_type>::print()
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

template <typename value_type>
void LinkedList<value_type>::push_front(const value_type & value)
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

template <typename value_type>
void LinkedList<value_type>::push_back(const value_type & value)
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

template <typename value_type>
value_type LinkedList<value_type>::pop_front()
{
	value_type result = this->head->value;

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

template <typename value_type>
value_type LinkedList<value_type>::pop_back()
{
	value_type result = this->tail->value;

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

template <typename value_type>
LinkedList<value_type>::Iterator LinkedList<value_type>::insert(Iterator before, const value_type & value)
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

template <typename value_type>
bool LinkedList<value_type>::operator!=(const LinkedList<value_type> & other) const
{
	LinkedList<value_type>::Iterator i;
	LinkedList<value_type>::Iterator j;

	for (i = this->begin(), j = other.begin(); i != this->end() || j != other.end(); i++, j++)
	{
		if (*i != *j)
		{
			return true;
		}
	}

	return false;
}

template <typename value_type>
bool LinkedList<value_type>::operator==(const LinkedList<value_type> & other) const
{
	return !(*this != other);
}

template <typename value_type>
LinkedList<value_type> LinkedList<value_type>::operator+(const LinkedList<value_type> & other) const
{
	LinkedList<value_type> result;

	result+=*this;
	result+=other;

	return result;
}

template <typename value_type>
LinkedList<value_type> & LinkedList<value_type>::operator+=(const LinkedList<value_type> & other)
{
	for (LinkedList::Iterator i = other.begin(); i != other.end(); i++)
	{
		this->push_back(*i);
	}

	return *this;
}

template <typename value_type>
LinkedList & LinkedList::operator+=(const value_type & value)
{
	this->push_back(value);

	return *this;
}

template <typename value_type>
LinkedList<value_type> & LinkedList<value_type>::operator=(const LinkedList<value_type> & other)
{
	this->clear();

	(*this) += other;//???

	return *this;
}
