#ifndef SSEMatrix_h
#define SSEMatrix_h

#include <iostream>
#include <vector>

#include <xmmintrin.h>

using namespace std;

class SSEMatrix
{
	private:
		float * table;
		int sizeX;
		int sizeY;
	public:
		SSEMatrix();
		SSEMatrix(int x, int y);
		SSEMatrix(const SSEMatrix & other);
		~SSEMatrix();

		float * operator[](int i);
		const float * operator[](int i) const;

		int width() const;
		int height() const;

		SSEMatrix transpose() const;

		double l() const;
		double w() const;

		SSEMatrix & operator+=( const SSEMatrix & other );
		SSEMatrix operator+( const SSEMatrix & other ) const;

		SSEMatrix & operator-=( const SSEMatrix & other );
		SSEMatrix operator-( const SSEMatrix & other ) const;

		SSEMatrix & operator*=( const SSEMatrix & other );
		SSEMatrix operator*( const SSEMatrix & other ) const;

		SSEMatrix & operator*=( const double & a);
		SSEMatrix operator*( const double & a) const;

		SSEMatrix operator/( const double & a ) const;
		SSEMatrix & operator/=( const double & a );

		SSEMatrix & operator=( const SSEMatrix & other );

		void print() const;
};

istream& operator>>(istream &in, SSEMatrix &matrix);
//ostream& operator<<(ostream &out, const SSEMatrix &matrix);

SSEMatrix E(const int size = 0);

SSEMatrix B(const SSEMatrix & A);
SSEMatrix R(SSEMatrix & A);

#endif
