#include <iomanip>

#include "FMatrix.h"

FMatrix::FMatrix()
:table(NULL), sizeX(0), sizeY(0)
{
}

FMatrix::FMatrix(int x, int y)
:table( new float[x*y] ), sizeX(x), sizeY(y)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			table[i*x+j] = 0;
		}
	}
}

FMatrix::FMatrix(const FMatrix & other)
:table( new float[other.sizeY * other.sizeX] ), sizeX(other.sizeX), sizeY(other.sizeY)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			this->table[i*sizeX+j] = other.table[i*other.sizeX+j];
		}
	}
}

FMatrix::~FMatrix()
{
	delete[] table;
}

float * FMatrix::operator[](int i)
{
	return &table[i*sizeX];
}

const float * FMatrix::operator[](int i) const
{
	return &table[i*sizeX];
}

int FMatrix::width() const
{
	return sizeX;
}

int FMatrix::height() const
{
	return sizeY;
}

FMatrix FMatrix::transpose() const
{
	FMatrix result( height(), width() );

	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			result[j][i] = (*this)[i][j];
		}
	}

	return result;
}

double FMatrix::l() const
{
	double max = 0;

	for (int i = 0; i < height(); i++)
	{
		max += (*this)[i][0];
	}

	double sum;

	for (int j = 1; j < width(); j++)
	{
		sum = 0;

		for (int i = 0; i < height(); i++)
		{
			sum += (*this)[i][j];
		}

		if ( sum > max )
		{
			max = sum;
		}
	}

	return max;
}

double FMatrix::w() const
{
	double max = 0;

	for (int j = 0; j < width(); j++)
	{
		max += (*this)[0][j];
	}

	double sum;

	for (int i = 1; i < height(); i++)
	{
		sum =0;

		for (int j = 0; j < width(); j++)
		{
			sum += (*this)[i][j];
		}

		if ( sum > max )
		{
			max = sum;
		}
	}

	return max;
}

FMatrix & FMatrix::operator*=(const FMatrix & other)
{
	FMatrix result( this->height(), other.width() );

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

FMatrix FMatrix::operator*(const FMatrix & other) const
{
	FMatrix result = E( this->height() );

	result *= (*this);
	result *= other;

	return result;
}

FMatrix & FMatrix::operator*=( const double & a )
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

FMatrix FMatrix::operator*( const double & a ) const
{
	FMatrix result(*this);

	result *= a;

	return result;
}

FMatrix & FMatrix::operator+=(const FMatrix & other)
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

FMatrix FMatrix::operator+(const FMatrix & other) const
{
	FMatrix result(*this);

	result += other;

	return result;
}

FMatrix & FMatrix::operator-=(const FMatrix & other)
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

FMatrix FMatrix::operator-(const FMatrix & other) const
{
	FMatrix result(*this);

	result -= other;

	return result;
}

FMatrix & FMatrix::operator=(const FMatrix & other)
{
	delete[] table;

	sizeX = other.sizeX;
	sizeY = other.sizeY;

	table = new float[ width() * height() ];

	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] = other[i][j];
		}
	}

	return *this;
}

FMatrix FMatrix::operator/( const double & a) const
{
	FMatrix result(*this);

	result /= a;

	return result;
}

FMatrix & FMatrix::operator/=( const double & a)
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

void FMatrix::print() const
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

istream& operator>>(istream & in, FMatrix & matrix)
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
ostream& operator<<(ostream & out, FMatrix & matrix)
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
FMatrix E(int size)
{
	FMatrix e(size, size);

	for (int i=0; i < size; i++)
	{
		e[i][i] = 1;
	}

	return e;
}

FMatrix B(const FMatrix & A)
{
	return A.transpose() / (A.l() * A.w());
}

FMatrix R(FMatrix & A)
{
	return E(A.width()) - (B(A)*A);
}
//E(A.width()) -
