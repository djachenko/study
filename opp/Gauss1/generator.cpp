#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>

#include "Matrix.h"

#define MATRIX

using namespace std;

int main()
{
	int size;

	cin >> size;

	srand(time(NULL));

	ofstream matrixOutput("matrix.bin", ios::binary);
	ofstream resultOutput("result.bin", ios::binary);
	ofstream sizeOutput("sizes.txt");

	sizeOutput << size << ' ' << size;

#ifdef MATRIX
	Matrix matrix(size, size);
	Matrix vector(1, size);
#else
	double ** matrix = new double*[size];

	for (int i = 0; i < size; i++)
	{
		matrix[i] = new double[size];
	}

	double * vector = new double[size];
#endif

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double x = (rand() % 10000) / 100.0; 

			matrix[i][j] = x;

			matrixOutput.write((char*)&x, sizeof(x));
		}

#ifdef MATRIX
		vector[i][0] = i + 1;
#else
		vector[i] = i + 1;
#endif

		cout << i << endl;
	}

	if (size <= 128)
	{
#ifdef MATRIX
		matrix.print();
#else
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << matrix[i][j];
			}

			cout << endl;
		}
#endif
	}

	cout << endl;

#ifdef MATRIX	
	Matrix result = matrix * vector;

	result.print();

	for (int i = 0; i < size; i++)
	{
		resultOutput.write((char*)&result[i][0], sizeof(result[i][0]));
	}
#else
	double * result = new double[size];

	for (int i = 0; i < size; i++)
	{
		result[i] = 0;

		for (int k = 0; k < size; k++)
		{
			result[i] += matrix[i][k] * vector[k];
		}
	}

	for (int i = 0; i < size; i++)
	{
		cout << result[i] << endl;
	}

	for (int i = 0; i < size; i++)
	{
		resultOutput.write((char*)&result[i], sizeof(result[i]));
	}

	for (int i = 0; i < size; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
	delete[] vector;
	delete[] result;
#endif

	matrixOutput.close();
	resultOutput.close();

	return 0;
}
