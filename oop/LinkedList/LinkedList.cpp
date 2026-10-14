#include <iostream>
#include <cstdlib>
#include "LinkedList.h"

using namespace std;

//<iterator>

LinkedList::iterator::iterator()
{
	pointer = NULL;
}

LinkedList::iterator::iterator(const iterator & other)
{
	this->pointer = other.pointer;
}

LinkedList::iterator::~iterator()
{
}

LinkedList::iterator & LinkedList::iterator::operator=(const iterator & other)
{
	this->pointer = other.pointer;

	return *this;
}

LinkedList::iterator & LinkedList::iterator::operator=(struct list * other)
{
	this->pointer = other;

	return *this;
}

bool LinkedList::iterator::operator!=(const iterator & other) const
{
	return !(*this == other);
}

bool LinkedList::iterator::operator==(const iterator & other) const
{
	return this->pointer == other.pointer;
}

value_type & LinkedList::iterator::operator*() const
{
	return this->pointer->value;
}

value_type * LinkedList::iterator::operator->() const
{
	return &(this->pointer->value);
}

LinkedList::iterator LinkedList::iterator::operator++()
{
	iterator temp =* this;

	this->pointer = this->pointer->next;

	return temp;
}

LinkedList::iterator & LinkedList::iterator::operator++(int)
{
	this->pointer = this->pointer->next;

	return *this;
}

LinkedList::iterator LinkedList::iterator::operator--()
{
	iterator temp =* this;

	this->pointer = this->pointer->previous;

	return temp;
}

LinkedList::iterator & LinkedList::iterator::operator--(int)
{
	this->pointer = this->pointer->previous;

	return *this;
}

void LinkedList::iterator::print()
{
	cout << "pointer: " << this->pointer << endl;
	cout << "value: " << this->pointer->value << endl;
	cout << "prev: " << this->pointer->previous << endl;
	cout << "next: " << this->pointer->next << endl;
	cout << endl;
}

//</iterator>

LinkedList::LinkedList()
:head(NULL), tail(NULL)
{
	first = head;
	last = NULL;
}

LinkedList::LinkedList(const LinkedList & other)
:head(NULL), tail(NULL)
{
	first = head;
	last = NULL;

	(*this)+=other;
}

LinkedList::~LinkedList()
{
	this->clear();
}

value_type & LinkedList::front()
{
	return this->head->value;
}

const value_type & LinkedList::front() const
{
	return this->head->value;
}

value_type & LinkedList::back()
{
	return this->tail->value;
}

const value_type & LinkedList::back() const
{
	return this->tail->value;
}

LinkedList::iterator LinkedList::begin() const
{
	return first;
}

LinkedList::iterator LinkedList::end() const
{
	return last;
}

bool LinkedList::contains(const value_type & value) const
{
	for (LinkedList::iterator i = this->begin(); i != this->end(); i++)
	{
		if (*i == value)
		{
			return true;
		}
	}

	return false;
}

int LinkedList::count(const value_type & value) const
{
	int result=0;

	for (LinkedList::iterator i = this->begin(); i != this->end(); i++)
	{
		if (*i == value)
		{
			result++;
		}
	}

	return result;
}

int LinkedList::size() const
{
	int result=0;

	for (LinkedList::iterator i = this->begin(); i != this->end(); i++)
	{
		result++;
	}

	return result;
}

bool LinkedList::empty() const
{
	return NULL != this->head;
}

LinkedList::iterator LinkedList::erase(iterator & pos)
{
	struct list * temp = pos.pointer;
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

LinkedList::iterator LinkedList::erase(iterator begin, iterator end)
{
	for (LinkedList::iterator i = begin; i != end;)
	{
		this->erase(i);
	}

	return end;
}

void LinkedList::clear()
{
	erase(this->begin(), this->end());
}

int LinkedList::removeAll(const value_type & value)
{
	int count=0;

	for (LinkedList::iterator i = this->begin(); i != this->end();)
	{
		if (*i == value)
		{
			this->erase(i);

			count ++;
		}
		else
		{
			i++;
		}
	}

	return count;
}

bool LinkedList::removeOne(const value_type & value)
{
	for (LinkedList::iterator i = this->begin(); i != this->end(); )
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

void LinkedList::print()
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

void LinkedList::push_front(const value_type & value)
{
	struct list * a = new struct list;
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

void LinkedList::push_back(const value_type & value)
{
	struct list * a = new struct list;
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

value_type LinkedList::pop_front()
{
	value_type result = this->head->value;

	struct list * temp = this->head;

	this->head = this->head->next;

	first = this->head;

	if (NULL == this->head)
	{
		this->tail = NULL;
	}

	delete temp;

	return result;
}

value_type LinkedList::pop_back()
{
	value_type result = this->tail->value;

	struct list * temp = this->tail;

	this->tail = this->tail->previous;

	if (NULL == this->tail)
	{
		this->head = NULL;

		first = this->head;
	}

	delete temp;

	return result;
}

LinkedList::iterator LinkedList::insert(iterator before, const value_type & value)
{
	struct list * ins = new struct list;

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

bool LinkedList::operator!=(const LinkedList & other) const
{
	LinkedList::iterator i;
	LinkedList::iterator j;

	for (i = this->begin(), j = other.begin(); i != this->end() || j != other.end(); i++, j++)
	{
		if (*i != *j)
		{
			return true;
		}
	}

	return false;
}

bool LinkedList::operator==(const LinkedList & other) const
{
	return !(*this != other);
}

LinkedList LinkedList::operator+(const LinkedList & other) const
{
	LinkedList result;
	
	result+=*this;
	result+=other;

	return result;
}

LinkedList & LinkedList::operator+=(const LinkedList & other)
{
	for (LinkedList::iterator i = other.begin(); i != other.end(); i++)
	{
		this->push_back(*i);
	}

	return *this;
}

LinkedList & LinkedList::operator+=(const value_type & value)
{
	this->push_back(value);

	return *this;
}

LinkedList & LinkedList::operator=(const LinkedList & other)
{
	this->clear();

	(*this) += other;//???

	return *this;
}
