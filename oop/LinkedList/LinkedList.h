#ifndef LinkedList_h
#define LinkedList_h

//#include <stdlib.h>

typedef int value_type;

class LinkedList
{
	private:
		struct list
		{
			value_type value;
			struct list * previous;
			struct list * next;
		};

		struct list * head;
		struct list * tail;
	public:
		class iterator
		{
			friend class LinkedList;
			private:
				struct list * pointer;
			public:		
				iterator();
				iterator(const iterator & other);
				~iterator();

				iterator & operator=(const iterator & other);
				iterator & operator=(struct list * other);

				bool operator!=(const iterator & other) const;
				bool operator==(const iterator & other) const;

				value_type & operator*() const;
				value_type * operator->() const;

				iterator operator++();
				iterator & operator++(int);
				iterator operator--();
				iterator & operator--(int);

				void print();
		};

		LinkedList();
		LinkedList(const LinkedList & other);
		~LinkedList();

		value_type & front();
		const value_type & front() const;
		value_type & back();
		const value_type & back() const;

		iterator begin() const;//needed for access from other methods
		iterator end() const;

		bool contains(const value_type & value) const;
		int count(const value_type & value) const;
		int size() const;
		bool empty() const;

		iterator erase(iterator & pos);
		iterator erase(iterator begin, iterator end);

		void clear();
		int removeAll(const value_type & value);
		bool removeOne(const value_type & value);

		void push_front(const value_type & value);
		void push_back(const value_type & value);
		value_type pop_front();
		value_type pop_back();

		iterator insert(iterator before, const value_type & value);

		bool operator!=(const LinkedList & other) const;//test!
		bool operator==(const LinkedList & other) const;
		LinkedList operator+(const LinkedList & other) const;//test!
		LinkedList & operator+=(const LinkedList & other);
		LinkedList & operator+=(const value_type & value);
		LinkedList & operator=(const LinkedList & other);

		void print();
	private:
		iterator first;
		iterator last;
};

#endif
