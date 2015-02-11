#include <stdlib.h>

#ifndef Pointer_h
#define Pointer_h

template <typename value_type>
class Pointer
{
	private:
		value_type * pointer;
	public:
		Pointer(value_type * p = NULL);
		Pointer(const Pointer & other);
		~Pointer();

		value_type * operator->() const;
		value_type * get() const;
		void reset(value_type * p = NULL);

		Pointer & operator=(const Pointer & other);
		value_type * release();

		void swap(Pointer & other);
};

template <typename value_type>
Pointer<value_type>::Pointer(value_type * p)
{
	pointer=p;
}

template <typename value_type>
Pointer<value_type>::Pointer(const Pointer & other)
{
	this->pointer=other.pointer;

	other.pointer=NULL;
}

template <typename value_type>
Pointer<value_type>::~Pointer()
{
	delete pointer;
}

template <typename value_type>
value_type * Pointer<value_type>::operator->() const
{
	return pointer;
}

template <typename value_type>
value_type * Pointer<value_type>::get() const
{
	return pointer;
}

template <typename value_type>
void Pointer<value_type>::reset(value_type * p)
{
	delete pointer;

	pointer=p;
}

template <typename value_type>
Pointer<value_type> & Pointer<value_type>::operator=(const Pointer & other)
{
	delete this->pointer;

	this->pointer=other.pointer;
	other.pointer=NULL;

	return *this;
}

template <typename value_type>
value_type * Pointer<value_type>::release()
{
	value_type * temp=pointer;

	pointer=NULL;

	return temp;
}

template <typename value_type>
void Pointer<value_type>::swap(Pointer & other)
{
	value_type * temp=this->poiner;

	this->pointer=other.pointer;
	other.pointer=temp;
}

#endif //Pointer
