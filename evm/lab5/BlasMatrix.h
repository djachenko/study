#ifndef BlasMatrix_h
#define BlasMatrix_h

#include <iostream>
#include <vector>

#include <cblas.h>

using namespace std;

class BlasMatrix
{
//	private:
	public:
		float * table;
		int sizeX;
		int sizeY;
		BlasMatrix();
		BlasMatrix(int x, int y);
		BlasMatrix(const BlasMatrix & other);
		~BlasMatrix();

		float * operator[](int i);
		const float * operator[](int i) const;

		int width() const;
		int height() const;

		BlasMatrix transpose() const;

		double l() const;
		double w() const;

		BlasMatrix & operator+=( const BlasMatrix & other );
		BlasMatrix operator+( const BlasMatrix & other ) const;

		BlasMatrix & operator-=( const BlasMatrix & other );
		BlasMatrix operator-( const BlasMatrix & other ) const;

		BlasMatrix & operator*=( const BlasMatrix & other );
		BlasMatrix operator*( const BlasMatrix & other ) const;

		BlasMatrix & operator*=( const double & a);
		BlasMatrix operator*( const double & a) const;

		BlasMatrix operator/( const double & a ) const;
		BlasMatrix & operator/=( const double & a );

		BlasMatrix & operator=( const BlasMatrix & other );

		void print() const;
};

istream& operator>>(istream &in, BlasMatrix &matrix);
//ostream& operator<<(ostream &out, const BlasMatrix &matrix);

BlasMatrix E(const int size = 0);

BlasMatrix B(const BlasMatrix & A);
BlasMatrix R(BlasMatrix & A);

#endif
