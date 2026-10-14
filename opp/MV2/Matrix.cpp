#include <iomanip>
#include <cstring>

#include "Matrix.h"

Matrix::Matrix()
:table(NULL), sizeX(0), sizeY(0)
{
}

Matrix::Matrix(int x, int y)
:table( new float[x*y] ), sizeX(x), sizeY(y)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			table[i*x+j] = 0;
		}
	}

	//memset(table, 0, x * j * sizeof(*table));
}

Matrix::Matrix(const Matrix & other)
:table( new float[other.sizeY * other.sizeX] ), sizeX(other.sizeX), sizeY(other.sizeY)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			this->table[i*sizeX+j] = other.table[i*other.sizeX+j];
		}
	}

	//memcpy((*this).table, other.table, other.width() * other.height());
}

Matrix::~Matrix()
{
	delete[] table;
}

float * Matrix::operator[](int i)
{
	return &table[i*sizeX];
}

const float * Matrix::operator[](int i) const
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

		table = new float[ width() * height() ];

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

float * Matrix::operator*()
{
	return table;
}

const float * Matrix::operator*() const
{
	return table;
}

void Matrix::print() const
{
	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			cout << setw(1) << (*this)[i][j] << ' ';
		}

		cout << endl;
	}
}

void Matrix::byteRead(istream & input)
{
//	cout << "byte" << this->width() * this->height() * sizeof(*table) << endl;;
	input.read((char*)table, this->width() * this->height() * sizeof(*table));
}

void Matrix::setTable(int x, int y)
{
	delete[] table;

	table = new float[x*y];
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


