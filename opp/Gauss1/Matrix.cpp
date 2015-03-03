#include <iomanip>
#include <cstring>

#include "Matrix.h"

Matrix::Matrix()
:table(NULL), sizeX(0), sizeY(0)
{
}

Matrix::Matrix(int x, int y)
:table( new double[x*y] ), sizeX(x), sizeY(y)
{
	memset(table, 0, x * y * sizeof(*table));
}

Matrix::Matrix(const Matrix & other)
:table( new double[other.sizeY * other.sizeX] ), sizeX(other.sizeX), sizeY(other.sizeY)
{
	memcpy((*this).table, other.table, other.width() * other.height() * sizeof(*((*this).table)));
}

Matrix::~Matrix()
{
	delete[] table;
}

double * Matrix::operator[](int i)
{
	return &table[i*sizeX];
}

const double * Matrix::operator[](int i) const
{
	return &table[i*sizeX];
}

int Matrix::width() const
{
	return sizeX;
}

int Matrix::height() const
{
	return sizeY;
}

Matrix Matrix::transpose() const
{
	Matrix result( height(), width() );

	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			result[j][i] = (*this)[i][j];
		}
	}

	return result;
}

Matrix & Matrix::operator+=(const Matrix & other)
{
	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] += other[i][j];
		}
	}

	return *this;
}

Matrix Matrix::operator+(const Matrix & other) const
{
	Matrix result(*this);

	result += other;

	return result;
}

Matrix & Matrix::operator-=(const Matrix & other)
{
	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] -= other[i][j];
		}
	}

	return *this;
}

Matrix Matrix::operator-(const Matrix & other) const
{
	Matrix result(*this);

	result -= other;

	return result;
}

Matrix & Matrix::operator*=(const Matrix & other)
{
	Matrix result(other.width(), this->height()); 

	for (int i = 0; i < result.height(); i++)
	{
		for (int j = 0; j < result.width(); j++)
		{
			for (int k = 0; k < this->width(); k++)
			{
				result[i][j] += (*this)[i][k] * other[k][j];
			}
		}
	}

	*this = result;

	return *this;
}

Matrix Matrix::operator*(const Matrix & other) const
{
	Matrix result = E( this->height() );//why? check

	result *= (*this);
	result *= other;

	return result;
}

Matrix & Matrix::operator*=( const double & a )
{
	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] *= a;
		}
	}

	return *this;
}

Matrix Matrix::operator*( const double & a ) const
{
	Matrix result(*this);

	result *= a;

	return result;
}

Matrix & Matrix::operator/=( const double & a)
{
	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] /= a;
		}
	}

	return *this;
}

Matrix Matrix::operator/( const double & a) const
{
	Matrix result(*this);

	result /= a;

	return result;
}

Matrix & Matrix::operator=(const Matrix & other)
{
	if (this != &other)
	{
		delete[] table;

		sizeX = other.sizeX;
		sizeY = other.sizeY;

		table = new double[ width() * height() ];

		//memset(table, 0, x * j * sizeof(*table));

		for (int i = 0; i < height(); i++)
		{
			for (int j = 0; j < width(); j++)
			{
				(*this)[i][j] = other[i][j];
			}
		}
	}

	return *this;
}

void Matrix::swapLines(const int firstLine, const int secondLine)
{
	int x = this->width();

	double * temp = new double[x];

	memcpy((*this)[firstLine], temp, x);
	memcpy((*this)[secondLine], (*this)[firstLine], x);
	memcpy(temp, (*this)[secondLine], x);

	delete[] temp;
}

double * Matrix::operator*()
{
	return table;
}

const double * Matrix::operator*() const
{
	return table;
}

void Matrix::print() const
{
	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			cout << setw(12) << (*this)[i][j] << ' ';
		}

		cout << endl;
	}
}

void Matrix::byteRead(istream & input)
{
	input.read((char*)table, this->width() * this->height() * sizeof(*table));
}

void Matrix::setTable(int x, int y)
{
	delete[] table;

	table = new double[x*y];
}

istream& operator>>(istream & in, Matrix & matrix)
{
	for (int i = 0; i < matrix.height(); i++)
	{
		for (int j = 0; j < matrix.width(); j++)
		{
			in >> matrix[i][j];
		}
	}

	return in;
}
/*
ostream& operator<<(ostream & out, Matrix & matrix)
{
	for (int i = 0; i < matrix.height(); i++)
	{
		for (int j = 0; j < matrix.width(); j++)
		{
			out << setw(5) <<  matrix[i][j] << ' ';
		}

		cout << endl;
	}

	return out;
}
*/
Matrix E(int size)
{
	Matrix e(size, size);

	for (int i=0; i < size; i++)
	{
		e[i][i] = 1;
	}

	return e;
}


