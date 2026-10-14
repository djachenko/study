#ifndef CircularBuffer_h
#define CircularBuffer_h

template <typename value_type>
class CircularBuffer
{
	private:
		value_type * buffer;
		int begin;
		int end;
		int quota;
		int number;
	public:
		CircularBuffer();
		CircularBuffer(const CircularBuffer & other);//ibo menyat pridetsya
		explicit CircularBuffer(int capacity);
		CircularBuffer(int capacity, const value_type & element);
		~CircularBuffer();

		value_type & operator[](int i);
		const value_type & operator[](int i) const;

		value_type & at(int i);
		const value_type & at(int i) const;

		value_type & front();
		const value_type & front() const;
		value_type & back();
		const value_type & back() const;

		value_type * linearize();
		bool is_linearized() const;

		void rotate(int new_begin);

		int size() const;
		bool empty() const;

		bool full() const;
		int reserve() const;
		int capacity() const;

		void set_capacity(int new_capacity);
		void resize(int new_size, const value_type & item);

		CircularBuffer & operator=(const CircularBuffer & other);
		void swap(CircularBuffer & cb);

		void push_back(const value_type & item);
		void push_front(const value_type & item);

		value_type pop_back();
		value_type pop_front();
		
		void insert(int pos, const value_type & item);

		void erase(int first, int last);
		void clear();
};

template <typename value_type>
bool operator==(const CircularBuffer<value_type> & a, const CircularBuffer<value_type> b);
template <typename value_type>
bool operator!=(const CircularBuffer<value_type> & a, const CircularBuffer<value_type> b);

enum CircularBufferException
{
	WrongIndex,
	WrongLimits,
	EmptyBuffer,
	QuotaConflict
};

//#include "CircularBuffer.cpp"

#endif //CircularBuffer_h
