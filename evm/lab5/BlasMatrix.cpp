#include <iomanip>

#include "BlasMatrix.h"

BlasMatrix::BlasMatrix()
:table(NULL), sizeX(0), sizeY(0)
{
}

BlasMatrix::BlasMatrix(int x, int y)
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

BlasMatrix::BlasMatrix(const BlasMatrix & other)
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

BlasMatrix::~BlasMatrix()
{
	delete[] table;
}

float * BlasMatrix::operator[](int i)
{
	return &table[ i * width() ];
}

const float * BlasMatrix::operator[](int i) const
{
	return &table[ i * width() ];
}

int BlasMatrix::width() const
{
	return sizeX;
}

int BlasMatrix::height() const
{
	return sizeY;
}

BlasMatrix BlasMatrix::transpose() const
{
	BlasMatrix result( height(), width() );

	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			result[j][i] = (*this)[i][j];
		}
	}

	return result;
}

double BlasMatrix::l() const
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

double BlasMatrix::w() const
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

BlasMatrix & BlasMatrix::operator*=(const BlasMatrix & other)
{
	BlasMatrix result( this->height(), other.width() );
/*
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

	BlasMatrix temp( this->height(), other.width() );
*/
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, this->height(), other.width(), this->width(), 1.0, &((*this)[0][0]), this->height(), &(other[0][0]), other.height(), 0.0, &(result[0][0]), result.height());

	*this = result;

	return *this;
}

BlasMatrix BlasMatrix::operator*(const BlasMatrix & other) const
{
	BlasMatrix result = E( this->height() );

	result *= (*this);
	result *= other;

	return result;
}

BlasMatrix & BlasMatrix::operator*=( const double & a )
{
	/*
	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] *= a;
		}
	}
	*/

	BlasMatrix other = E(this->width());
	BlasMatrix result = E(this->width());

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, this->height(), other.width(), this->width(), a, &((*this)[0][0]), this->height(), &(other[0][0]), other.height(), 0.0, &(result[0][0]), result.height());

	*this = result;

	return *this;
}

BlasMatrix BlasMatrix::operator*( const double & a ) const
{
	BlasMatrix result(*this);

	result *= a;

	return result;
}

BlasMatrix & BlasMatrix::operator+=(const BlasMatrix & other)
{
	/*
	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] += other[i][j];
		}
	}
	*/

	BlasMatrix result = other;

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, this->height(), this->width(), this->width(), 1.0, &((*this)[0][0]), this->height(), &( ( E(this->width()) )[0][0]), this->width(), 1.0, &(result[0][0]), result.height());

	*this = result;

	return *this;
}

BlasMatrix BlasMatrix::operator+(const BlasMatrix & other) const
{
	BlasMatrix result(*this);

	result += other;

	return result;
}

BlasMatrix & BlasMatrix::operator-=(const BlasMatrix & other)
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

BlasMatrix BlasMatrix::operator-(const BlasMatrix & other) const
{
	BlasMatrix result(*this);

	result -= other;

	return result;
}

BlasMatrix & BlasMatrix::operator=(const BlasMatrix & other)
{
	//delete[] table;

	sizeX = other.sizeX;
	sizeY = other.sizeY;

	/*table = new float[ height() * width() ];

	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] = other[i][j];
		}
	}
	*/

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, other.height(), other.width(), other.width(), 1.0, &(other[0][0]), other.height(), &((E(other.width()))[0][0]), other.width(), 0.0, &((*this)[0][0]), this->height());

	return *this;
}

BlasMatrix BlasMatrix::operator/( const double & a) const
{
	BlasMatrix result(*this);

	result /= a;

	return result;
}

BlasMatrix & BlasMatrix::operator/=( const double & a)
{
	/*for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			(*this)[i][j] /= a;
		}
	}
	*/

	(*this)*=(1.0/a);

	return *this;
}

void BlasMatrix::print() const
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

istream& operator>>(istream & in, BlasMatrix & matrix)
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
ostream& operator<<(ostream & out, BlasMatrix & matrix)
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
BlasMatrix E(int size)
{
	BlasMatrix e(size, size);

	for (int i=0; i < size; i++)
	{
		e[i][i] = 1;
	}

	return e;
}

BlasMatrix B(const BlasMatrix & A)
{
	return A.transpose() / (A.l() * A.w());
}

BlasMatrix R(BlasMatrix & A)
{
	return E(A.width()) - (B(A)*A);
}
//E(A.width()) -
