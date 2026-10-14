#ifndef FMatrix_h
#define FMatrix_h

#include <iostream>
#include <vector>

using namespace std;

class FMatrix
{
//	private:
	public:
		float * table;
		int sizeX;
		int sizeY;
		FMatrix();
		FMatrix(int x, int y);
		FMatrix(const FMatrix & other);
		~FMatrix();

		float * operator[](int i);
		const float * operator[](int i) const;

		int width() const;
		int height() const;

		FMatrix transpose() const;

		double l() const;
		double w() const;

		FMatrix & operator+=( const FMatrix & other );
		FMatrix operator+( const FMatrix & other ) const;

		FMatrix & operator-=( const FMatrix & other );
		FMatrix operator-( const FMatrix & other ) const;

		FMatrix & operator*=( const FMatrix & other );
		FMatrix operator*( const FMatrix & other ) const;

		FMatrix & operator*=( const double & a);
		FMatrix operator*( const double & a) const;

		FMatrix operator/( const double & a ) const;
		FMatrix & operator/=( const double & a );

		FMatrix & operator=( const FMatrix & other );

		void print() const;
};

istream& operator>>(istream &in, FMatrix &matrix);
//ostream& operator<<(ostream &out, const FMatrix &matrix);

FMatrix E(const int size = 0);

FMatrix B(const FMatrix & A);
FMatrix R(FMatrix & A);

#endif
