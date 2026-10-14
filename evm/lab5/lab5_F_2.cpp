#include <iostream>
#include <fstream>

#include <stdlib.h>

#define size 6

int main()
{
	ifstream input;

	input.open("lab5.txt");

	float A[size][size];

	for (int i = 0; i < matrix.height(); i++)
	{
		for (int j = 0; j < matrix.width(); j++)
		{
			input >> matrix[i][j];
		}
	}

	input.close();

	float result[size][size];

	FMatrix r = E( A.height() );
	FMatrix matR = R(A);
	FMatrix matB = B(A);
//start
	for (int i = 0; i < 1000000; i++)
	{
		result += r;

		r *= matR;
	}

	result *= matB;
//finish

	result.print();

	cout << endl;

	(A * result).print();

	return 0;
}

