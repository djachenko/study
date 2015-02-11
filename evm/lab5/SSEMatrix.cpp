#include <iomanip>

#include "SSEMatrix.h"

SSEMatrix::SSEMatrix()
:table(NULL), sizeX(0), sizeY(0)
{
}

SSEMatrix::SSEMatrix(int x, int y)
:table( new float[x*y] ), sizeX(x), sizeY(y)
{
	__m128 * t;

	for (int i = 0; i < sizeY; i++)
	{
		t = (__m128 *)(&table[i*x]);

		for (int j = 0; j < sizeX/4; j++)
		{
			t[j] = _mm_set_ps1(0);
		}
	}
}

SSEMatrix::SSEMatrix(const SSEMatrix & other)
:table( new float[other.sizeX * other.sizeY] ), sizeX(other.sizeX), sizeY(other.sizeY)
{
	__m128 * x;

	for (int i = 0; i < sizeY; i++)
	{
		x = (__m128 *)other[i];

		for (int j = 0; j < sizeX/4; j++)
		{
			_mm_prefetch((char *)&x[i+4],_MM_HINT_NTA);
			_mm_storeu_ps( &(this->table[i*sizeX+j*4]), x[j]);
		}
	}
}

SSEMatrix::~SSEMatrix()
{
	delete[] table;
}

float * SSEMatrix::operator[](int i)
{
	return table + i * sizeX;
}

const float * SSEMatrix::operator[](int i) const
{
	return table + i * sizeX;
}

int SSEMatrix::width() const
{
	return sizeX;
}

int SSEMatrix::height() const
{
	return sizeY;
}

SSEMatrix SSEMatrix::transpose() const
{
	SSEMatrix result( height(), width() );

	for (int i = 0; i < height(); i++)
	{
		for (int j = 0; j < width(); j++)
		{
			result[j][i] = (*this)[i][j];
		}
	}

	return result;
}

double SSEMatrix::l() const
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

double SSEMatrix::w() const
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

SSEMatrix & SSEMatrix::operator*=(const SSEMatrix & other)
{
	SSEMatrix result( this->height(), other.width() );

	SSEMatrix that = other.transpose();

	__m128 * x;
	__m128 * y;

	__m128 p;
	__m128 s;

	for (int i = 0; i < result.height(); i++)
	{
		x = (__m128 *)(*this)[i];

		for (int j = 0; j < result.width(); j++)
		{
			y = (__m128 *)that[j];

			s = _mm_set_ps1(0);

			for (int k = 0; k < this->width()/4; k++)
			{
				_mm_prefetch((char *)&x[i+4],_MM_HINT_NTA);
				_mm_prefetch((char *)&y[i+4],_MM_HINT_NTA);

				p = _mm_mul_ps( x[k], y[k] );
				s = _mm_add_ps( s, p );
			}

			p=_mm_movehl_ps(p, s); // перемещение двух старших значений s в младшие p
			s=_mm_add_ps(s, p);    // векторное сложение
			p=_mm_shuffle_ps(s, s, 1); //перемещение второго значения в s в младшую позицию в p
			s=_mm_add_ss(s, p);    // скалярное сложение
			_mm_store_ss(&result[i][j], s); // запись младшего значения в память
		}
	}

	*this = result;

	return *this;
}

SSEMatrix SSEMatrix::operator*(const SSEMatrix & other) const
{
	SSEMatrix result = E( this->height() );

	result *= (*this);
	result *= other;

	return result;
}

SSEMatrix & SSEMatrix::operator*=( const double & a )
{
	__m128 x = _mm_set_ps1(a);
	__m128 * y;

	for (int i = 0; i < height(); i++)
	{
		y = (__m128 *)(*this)[i];

		for (int j = 0; j < width()/4; j++)
		{
			_mm_prefetch((char *)&y[i+4],_MM_HINT_NTA);

			y[j] = _mm_mul_ps( y[j], x);
		}
	}

	return *this;
}

SSEMatrix SSEMatrix::operator*( const double & a ) const
{
	SSEMatrix result(*this);

	result *= a;

	return result;
}

SSEMatrix & SSEMatrix::operator+=(const SSEMatrix & other)
{
	__m128 * x;
	__m128 * y;

	for (int i = 0; i < height(); i++)
	{
		x = (__m128 *)(*this)[i];
		y = (__m128 *)other[i];

		for (int j = 0; j < width()/4; j++)
		{
			_mm_prefetch((char *)&x[i+4],_MM_HINT_NTA);
			_mm_prefetch((char *)&y[i+4],_MM_HINT_NTA);

			x[j] = _mm_add_ps(x[j], y[j]);
		}
	}

	return *this;
}

SSEMatrix SSEMatrix::operator+(const SSEMatrix & other) const
{
	SSEMatrix result(*this);

	result += other;

	return result;
}

SSEMatrix & SSEMatrix::operator-=(const SSEMatrix & other)
{
	__m128 * x;
	__m128 * y;

	for (int i = 0; i < height(); i++)
	{
		x = (__m128 *)(*this)[i];
		y = (__m128 *)other[i];

		for (int j = 0; j < width()/4; j++)
		{
			_mm_prefetch((char *)&x[i+4],_MM_HINT_NTA);
			_mm_prefetch((char *)&y[i+4],_MM_HINT_NTA);

			x[j] = _mm_sub_ps(x[j], y[j]);
		}
	}

	return *this;
}

SSEMatrix SSEMatrix::operator-(const SSEMatrix & other) const
{
	SSEMatrix result(*this);

	result -= other;

	return result;
}

SSEMatrix & SSEMatrix::operator=(const SSEMatrix & other)
{
	delete[] table;

	sizeX = other.sizeX;
	sizeY = other.sizeY;

	table = new float[ width() * height() ];

	__m128 * x;

	for (int i = 0; i < height(); i++)
	{
		x = (__m128 *)other[i];

		for (int j = 0; j < width()/4; j++)
		{
			_mm_prefetch((char *)&x[i+4],_MM_HINT_NTA);

			_mm_storeu_ps( table + i * sizeX + j * 4, x[j]);
		}
	}

	return *this;
}

SSEMatrix SSEMatrix::operator/( const double & a) const
{
	SSEMatrix result(*this);

	result /= a;

	return result;
}

SSEMatrix & SSEMatrix::operator/=( const double & a)
{
	__m128 x = _mm_set_ps1(a);
	__m128 * y;

	for (int i = 0; i < height(); i++)
	{
		y = (__m128 *)(*this)[i];

		for (int j = 0; j < width()/4; j++)
		{
			_mm_prefetch((char *)&y[i+4],_MM_HINT_NTA);

			y[j] = _mm_div_ps( y[j], x);
		}
	}

	return *this;
}

void SSEMatrix::print() const
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

istream& operator>>(istream & in, SSEMatrix & matrix)
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
ostream& operator<<(ostream & out, SSEMatrix & matrix)
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
SSEMatrix E(int size)
{
	SSEMatrix e(size, size);

	for (int i=0; i < size; i++)
	{
		e[i][i] = 1;
	}

	return e;
}

SSEMatrix B(const SSEMatrix & A)
{
	return A.transpose() / (A.l() * A.w());
}

SSEMatrix R(SSEMatrix & A)
{
	return E(A.width()) - (B(A)*A);
}
//E(A.width()) -
