#include <iostream>
#include <cstdlib>
#include "CircularBuffer.h"

using namespace std;

template <typename value_type>
CircularBuffer<value_type>::CircularBuffer()
:buffer(NULL), begin(0), end(0), quota(0), number(0)
{
}

template <typename value_type>
CircularBuffer<value_type>::CircularBuffer(const CircularBuffer & other)
:begin(other.begin), end(other.end), quota(other.quota), number(other.number)
{
	this->buffer=new value_type[this->quota];

	for (int i=0;i<this->quota;i++)
	{
		this->buffer[i]=other.buffer[i];
	}
}

template <typename value_type>
CircularBuffer<value_type>::CircularBuffer(int capacity)
:begin(0), end(0), quota(capacity), number(0)
{
	buffer=new value_type[capacity];
}

template <typename value_type>
CircularBuffer<value_type>::CircularBuffer(int capacity, const value_type & element)
:begin(0), end(0), quota(capacity), number(capacity)
{
	buffer=new value_type[capacity];

	for (int i=0;i<this->quota;i++)
	{
		this->buffer[i]=element;
	}
}

template <typename value_type>
CircularBuffer<value_type>::~CircularBuffer()
{
	delete[] this->buffer;
}

template <typename value_type>
value_type & CircularBuffer<value_type>::operator[](int i)
{
	//printf("i %d buf %d\n",i,buffer[(begin+i)%quota]);

	return this->buffer[(begin+i)%quota];
}

template <typename value_type>
const value_type & CircularBuffer<value_type>::operator[](int i) const
{
	return (*this)[i];
}

template <typename value_type>
value_type & CircularBuffer<value_type>::at(int i)
{
	if (i<0 || i>number-1)
	{
		throw WrongIndex;
	}

	return this->buffer[(begin+i)%quota];
}

template <typename value_type>
const value_type & CircularBuffer<value_type>::at(int i) const
{
	if (i<0 || i>number)
	{
		throw WrongIndex;
	}

	return this->at(i);
}

template <typename value_type>
value_type & CircularBuffer<value_type>::front()
{
	if (0==number)
	{
		throw EmptyBuffer;
	}

	return this->buffer[this->begin];
}

template <typename value_type>
const value_type & CircularBuffer<value_type>::front() const
{	
	return this->front();
}

template <typename value_type>
value_type & CircularBuffer<value_type>::back()
{
	if (0==number)
	{
		throw EmptyBuffer;
	}

	return buffer[(end-1+quota)%quota];
}

template <typename value_type>
const value_type & CircularBuffer<value_type>::back() const
{
	return this->back();
}

template <typename value_type>
value_type * CircularBuffer<value_type>::linearize()
{
	if (!this->buffer)
	{
		return NULL;
	}

	this->rotate(0);

	return this->buffer;
}

template <typename value_type>
bool CircularBuffer<value_type>::is_linearized() const
{
	return (this->begin==0);
}

template <typename value_type>
void CircularBuffer<value_type>::rotate(int new_begin)
{
	if (this->buffer==NULL)
	{
		throw EmptyBuffer;
	}

	if (new_begin<0 || new_begin>number)
	{
		throw WrongIndex;
	}

	value_type * temp=new value_type[this->quota];

	for (int i=0; i<this->quota; i++)
	{
		temp[i]=(*this)[(new_begin+i)%quota];
	}

	delete[] this->buffer;

	this->buffer=temp;

	this->begin=0;
	this->end=number;
}

template <typename value_type>
int CircularBuffer<value_type>::size() const
{
	return this->number;
}

template <typename value_type>
bool CircularBuffer<value_type>::empty() const
{
	return (this->size()==0);
}

template <typename value_type>
bool CircularBuffer<value_type>::full() const
{
	return (0==this->reserve() && number);
}

template <typename value_type>
int CircularBuffer<value_type>::reserve() const
{
	return quota-number;
}

template <typename value_type>
int CircularBuffer<value_type>::capacity() const
{
	return quota;
}

template <typename value_type>
void CircularBuffer<value_type>::set_capacity(int new_capacity)
{
	value_type * temp=new value_type[new_capacity];

	for (int i=0; i<this->size() && i<new_capacity; i++)
	{
		temp[i]=(*this)[i];
	}

	delete[] this->buffer;

	begin=0;
	buffer=temp;
	quota=new_capacity;

	if (number>=new_capacity)
	{
		end=0;
	}
	else
	{
		end=number;
	}

	if (number>new_capacity)
	{
		number=new_capacity;
	}
}

template <typename value_type>
void CircularBuffer<value_type>::resize(int new_size, const value_type & item)
{
	this->set_capacity(new_size);

	for (; this->reserve(); )
	{
		this->push_back(item);//ask
	}
}

template <typename value_type>
CircularBuffer<value_type> & CircularBuffer<value_type>::operator=(const CircularBuffer & other)
{
	this->begin=other.begin;
	this->end=other.end;
	this->quota=other.quota;
	this->number=other.number;

	value_type * temp=new value_type[this->quota];

	for (int i=0; i<other.quota; i++)
	{
		temp[i]=other.buffer[i];
	}

	delete[] this->buffer;

	this->buffer=temp;

	return *this;
}

template <typename value_type>
void CircularBuffer<value_type>::swap(CircularBuffer & other)
{
	if (this->quota!=other.quota)
	{
		throw QuotaConflict;
	}

	value_type b;

	for (int i=0; i<this->quota; i++)
	{
		b=(*this)[i];
		(*this)[i]=other[i];
		other[i]=b;
	}
}

template <typename value_type>
void CircularBuffer<value_type>::push_back(const value_type & item)
{
	if (this->number==this->quota)
	{
		begin=(begin+1)%quota;
	}
	else
	{
		number++;
	}

	buffer[end]=item;

	end=(end+1)%quota;
}

template <typename value_type>
void CircularBuffer<value_type>::push_front(const value_type & item)
{
	if (this->number==this->quota)
	{
		end=(end-1+quota)%quota;
	}
	else
	{
		number++;
	}

	begin=(begin-1+quota)%quota;

	buffer[begin]=item;
}

template <typename value_type>
value_type CircularBuffer<value_type>::pop_back()
{
	if (number==0)
	{
		throw EmptyBuffer;
	}

	end=(end-1+quota)%quota;

	number--;

	return buffer[end];
}

template <typename value_type>
value_type CircularBuffer<value_type>::pop_front()
{
	if (number==0)
	{
		throw EmptyBuffer;
	}

	int result=buffer[begin];

	begin=(begin+1)%quota;

	number--;

	return result;
}

template <typename value_type>
void CircularBuffer<value_type>::insert(int pos, const value_type & item)
{
	if (pos<0 || pos>number)
	{
		throw WrongIndex;
	}

	buffer[(begin+pos)%quota]=item;
}

template <typename value_type>
void CircularBuffer<value_type>::erase(int first, int last)
{
	if (first<0 || first>number)
	{
		throw WrongIndex;
	}

	if (last<0 || last>number)
	{
		throw WrongIndex;
	}

	if (first > last)
	{
		throw WrongLimits;
	}

	int delta=last-first;

	for (int i=first; i<number-delta; i++)
	{
		buffer[i]=buffer[(i+delta)%quota];
	}

	number-=delta;
	end=(end+quota-delta)%quota;
}

template <typename value_type>
void CircularBuffer<value_type>::clear()
{
	this->erase(0,this->size());
}

template <typename value_type>
bool operator==(const CircularBuffer<value_type> & a, const CircularBuffer<value_type> & b)
{
	if (a.size()!=b.size() && a.reserve()!=b.reserve())
	{
		return false;
	}

	for (int i=0; i<a.size(); i++)
	{
		if (a.at(i)!=b.at(i))
		{
			return false;
		}
	}

	return true;
}

template <typename value_type>
bool operator!=(const CircularBuffer<value_type> & a, const CircularBuffer<value_type> & b)
{
	return !(a==b);
}
