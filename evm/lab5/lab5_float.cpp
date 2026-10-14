#include <iostream>
#include <fstream>

#include <stdlib.h>

#define size 6

float ** make_matrix( int n )
{
	float ** matrix;

	matrix = malloc( n * sizeof( *matrix ) );

	for (int i = 0; i < N; i++)
	{
		matrix[i] = malloc( n * sizeof( *matrix[i] ) );
	}

	return matrix;
}

int main()
{
	ifstream input;

	input.open("lab5.txt");

	float **lab5 = make_matrix(N);

	float ** b = make_matrix(N);

	for (int i = 0; i < N; i++)//b = lab5^T
	{
		for (int j = 0; j < N; j++)
		{
			b[i][j] = lab5[j][i];
			b[j][i] = lab5[i][j];
		}
	}

	float l = 0;
	float w = 0;

	for (int i = 0; i < N; i++)
	{
		l += lab5[i][0];
		w += lab5[0][i];
	}

	float suml;
	float sumw;

	for (int i = 1; i < N; i++)
	{
		suml = 0;
		sumw = 0;

		for (int j = 0; j < N; j++)
		{
			suml += lab5[j][i];
			sumw += lab5[i][j];
		}

		if ( suml > l )
		{
			l = suml;
		}

		if ( sumw > w )
		{
			w = sumw;
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			b[i][j]/=(l*w);
		}
	}

	float ** R = make_matrix(N);

	for (int i = 0; i < N; i++)//R = lab5*b
	{
		for (int j = 0; j < N; j++)
		{
			R[i][j] = 0;

			for (int k = 0; k < N; k++)
			{
				R[i][j] += lab5[i][k] * b[k][j];;
			}
		}
	}

	for (int i = 0; i < N; i++)//R = (R-E)*-1, t.e. R = E - R
	{
		R[i][i] -= 1;

		for (int j = 0; j < N; j++)
		{
			R[i][j] *= -1;
		}
	}

	float ** result = make_matrix(N);

	for (int i = 0; i < N; i++)//result = E
	{
		for (int j = 0; j < N; j++)
		{
			result[i][j] = 0;
		}

		result[i][i] = 1;
	}

	float ** r = make_matrix(N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			r[i][j] = R[i][j];
		}
	}

	for (int count = 0; count < 1000; count++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				result[i][j] += r[i][j];
			}
		}

		for (int i = 0; i < N; i++)
		{
		}
		
	}

	return 0;
}
