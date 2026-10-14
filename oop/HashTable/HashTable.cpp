#include "HashTable.h"

#include <iostream>

using namespace std;

HashTable::HashTable()
:table(new Element*[SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
	table[i] = new Element;
	table[i]->next = NULL;
	}
}

HashTable::~HashTable()
{
clear();
	for (int i = 0; i < SIZE; i++)
	{
	delete table[i];
	}
delete[] table;
}

HashTable::HashTable(const HashTable& b)
{
	for (int i = 0; i < SIZE; i++)
	{
	Element *currentElement = table[i];
	Element *otherElement = b.table[i];
		while (otherElement != NULL)
		{
		Value newValue = otherElement->value;
		Element *newElement = new Element;
		newElement->value = newValue;
		newElement->next = NULL;
		currentElement->next = newElement;
		otherElement = otherElement->next;
		currentElement = currentElement->next;
		}
	}
}

void HashTable::swap(HashTable& b)
{
	Element **temp = table;
	table = b.table;
	b.table = temp;
}

HashTable& HashTable::operator=(const HashTable& b)
{
	clear();

	for (int i = 0; i < SIZE; i++)
	{
		Element *currentElement = table[i];
		Element *otherElement = b.table[i];
		
		while (otherElement != NULL)
		{
			Value newValue = otherElement->value;
			Element *newElement = new Element;
	
			newElement->value = newValue;
			newElement->next = NULL;
	
			currentElement->next = newElement;
			otherElement = otherElement->next;
			currentElement = currentElement->next;
		}
	}
	
	return *this;
}

void HashTable::clear()
{
	for (int i = 0; i < SIZE; i++)
	{
		
		Element *current = table[i]->next;
		while (current != NULL)
		{
			Element *next = current->next;
			delete current;
			current = next;
		}
	
		table[i]->next = NULL;
	}
}

bool HashTable::erase(const Key& k)
{
int hash = hashFunction(k);
Element *prev = table[hash];
Element *curr = table[hash]->next;

	while ((curr != NULL) && (curr->key != k))
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr != NULL)
	{
		prev->next = curr->next;
		delete curr;
	}
return curr != NULL;
}

bool HashTable::insert(const Key& k, const Value& v)
{
	int hash = hashFunction(k);
	
	if (contains(k))
	{
		erase(k);
	}

	Element *element = new Element();

	if (element != NULL)
	{
		element->value = v;
		element->key = k;
		
		element->next = table[hash]->next;
		table[hash]->next = element;
	
		return true;
	}
	else
	{
		return false;
	}
}

bool HashTable::contains(const Key& k) const
{
int hash = hashFunction(k);
Element *p = table[hash]->next;

	while (p != NULL && p->key != k)
	{
		p = p->next;
	}

return NULL != p;
}

Value& HashTable::operator[](const Key& k)
{
	int hash = hashFunction(k);
	Element *p = table[hash]->next;

	while (p != NULL && p->key != k)
	{
		//cout << (int)p << ' ' << p->key << endl;
		p = p->next;
	}

	if (p != NULL)
	{
		return p->value;
	}
	else
	{
		insert(k, Value());
		return (*this)[k];
	}
}

Value& HashTable::at(const Key& k)
{
	int hash = hashFunction(k);
	Element *p = table[hash]->next;

	while (p != NULL && p->key != k)
	{
		p = p->next;
	}

	if (p != NULL)
	{
		return p->value;
	}
	else
	{
		throw ElementNotFoundException;
	}
}

const Value& HashTable::at(const Key& k) const
{
	int hash = hashFunction(k);
	Element *p = table[hash]->next;

	while (p != NULL && p->key != k)
	{
		p = p->next;
	}

	if (p != NULL)
	{
		return p->value;
	}
	else
	{
		throw ElementNotFoundException;
	}
}

int HashTable::size() const
{
	int count = 0;

	for (int i = 0; i < SIZE; i++)
	{
	   for (Element *p = table[i]->next; p != NULL; p = p->next)
		{
			count++;
		}
	}

	return count;
}

bool HashTable::empty() const
{
	return 0 == size();
}

int HashTable::hashFunction(const Key& key) const
{
	int l = key.length();
	int sum = 0;

	for (int i = 0; i < l; i++)
	{
		sum = sum * 37 + key[i];
		sum %= SIZE;
	}
	
	return sum;
}

bool operator==(const HashTable & a, const HashTable & b)
{
	if (a.size() != b.size())
	{
		return false;
	}

	for (int i = 0; i < SIZE; i++)
	{
		HashTable::Element *p = a.table[i]->next;
		HashTable::Element *q = b.table[i]->next;
		
		while (q != NULL && p != NULL)
		{
			if (q->key != p->key ||
			(q->value).age != (p->value).age ||
			(q->value).weight != (p->value).weight)
			{
				return false;
			}
			else
			{
				p = p->next;
				q = q->next;
			}
		}
		if (q != NULL || p != NULL)
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const HashTable & a, const HashTable & b)
{
	return !(a == b);
}


