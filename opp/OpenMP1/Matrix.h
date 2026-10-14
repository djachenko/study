#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
private:
	double * table;
	int sizeX;
	int sizeY;

public:
	Matrix();
	Matrix(int x, int y);
	Matrix(const Matrix & other);
	virtual ~Matrix();

	double * operator[](int i);
	const double * operator[](int i) const;

	int width() const;
	int height() const;

	Matrix transpose() const;

	virtual Matrix & operator+=( const Matrix & other );
	virtual Matrix operator+( const Matrix & other ) const;

	virtual Matrix & operator-=( const Matrix & other );
	virtual Matrix operator-( const Matrix & other ) const;

	virtual Matrix & operator*=( const Matrix & other );
	virtual Matrix operator*( const Matrix & other ) const;

	virtual Matrix & operator*=( const double & a);
	virtual Matrix operator*( const double & a) const;

	virtual Matrix & operator/=( const double & a );
	virtual Matrix operator/( const double & a ) const;

	virtual Matrix & operator=( const Matrix & other );

	void swapLines(const int firstLine, const int secondLine);

	double * operator*();
	const double * operator*() const;

	void print() const;
	void byteRead(istream & input);

protected:
	void setTable(int x, int y);
};

istream& operator>>(istream &in, Matrix &matrix);
//ostream& operator<<(ostream &out, const Matrix &matrix);

Matrix E(const int size = 0);

#endif
