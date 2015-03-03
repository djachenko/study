#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>

#include "Matrix.h"

using namespace std;

int main()
{
	int size;

	cin >> size;

	srand(time(NULL));

	ofstream matrixOutput("matrix.bin", ios::binary);
	ofstream sizeOutput("sizes.txt");

	sizeOutput << size << ' ' << size;

	Matrix matrix(size, size);
	Matrix vector(1, size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double x = rand() % 10;//000 / 100.0; 

			matrix[i][j] = x;

	//		cout << setw(5) << x << ' ';

			matrixOutput.write((char*)&x, sizeof(x));
		}

		double y = i+1;// rand() % 10000 / 100.0;

		vector[i][0] = y;
	}

	Matrix result = matrix * vector;

	result.print();

	ofstream vectorOutput("vector.bin", ios::binary);

	for (int i = 0; i < size; i++)
	{
		vectorOutput.write((char*)&vector[i][0], sizeof(vector[i][0]));
	}

	matrixOutput.close();
	vectorOutput.close();

	return 0;
}
