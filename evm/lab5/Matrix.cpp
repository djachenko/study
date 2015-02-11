#include <iomanip>

#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(int x, int y)
:table(x, vector<double>(y, 0)), sizeX(x), sizeY(y)
{
}

Matrix::Matrix(const Matrix & other)
:table(other.table), sizeX(other.sizeX), sizeY(other.sizeY)
{
}

Matrix::~Matrix()
{
}

vector<double> & Matrix::operator[](int i)
{
	return table[i];
}

const vector<double> & Matrix::operator[](int i) const
{
	return table[i];
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
	Matrix result(sizeY, sizeX);

	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			result[j][i] = (*this)[i][j];
		}
	}

	return result;
}

double Matrix::l() const
{
	double max = 0;

	for (int i = 0; i < width(); i++)
	{
		max += (*this)[0][i];
	}

	double sum;

	for (int j = 1; j < height(); j++)
	{
		sum = 0;

		for (int i = 0; i < width(); i++)
		{
			sum += (*this)[j][i];
		}

		if ( sum > max )
		{
			max = sum;
		}
	}

	return max;
}

double Matrix::w() const
{
	double max = 0;

	for (int j = 0; j < height(); j++)
	{
		max += (*this)[j][0];
	}

	double sum;

	for (int i = 1; i < width(); i++)
	{
		sum =0;

		for (int j = 0; j < height(); j++)
		{
			sum += (*this)[j][i];
		}

		if ( sum > max )
		{
			max = sum;
		}
	}

	return max;
}

Matrix & Matrix::operator*=(const Matrix & other)
{
	Matrix result( this->height(), other.width() );

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
	Matrix result = E( this->height() );

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

Matrix & Matrix::operator=(const Matrix & other)
{
	sizeX = other.sizeX;
	sizeY = other.sizeY;

	table = other.table;

	return *this;
}

Matrix Matrix::operator/( const double & a) const
{
	Matrix result(*this);

	result /= a;

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

Matrix E(int size)
{
	Matrix e(size, size);

	for (int i=0; i < size; i++)
	{
		e[i][i] = 1;
	}

	return e;
}

Matrix B(const Matrix & A)
{
	return A.transpose() / (A.l() * A.w());
}

Matrix R(const Matrix & A)
{
	return E(A.width()) - (B(A)*A);
}
