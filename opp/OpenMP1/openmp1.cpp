#include <fstream>
#include <iostream>
#include <omp.h>
#include <cstring>

#define comm MPI_COMM_WORLD

using namespace std;

int main(int argc, char ** argv)
{
for (int threads = 1; threads < 17; threads++)
{
	omp_set_num_threads(threads);
	int size;
	int rank;

	ifstream sizeInput;
	sizeInput.open("sizes.txt");

	int x;
	int y;

	sizeInput >> x >> y;

	double * matrix = new double[y * x];

	double * vector = new double[x];

	ifstream matrixInput("matrix.bin", ios::binary);
	ifstream vectorInput("vector.bin", ios::binary);
	
	matrixInput.read((char*)matrix, x * y * sizeof(*matrix));
	vectorInput.read((char*)vector, x * sizeof(*vector));

	double * result = new double[y];
	memset(result, 0, y * sizeof(*result));

	double start = omp_get_wtime();

	for (int count = 0; count < 10; count++)
	{
	#pragma omp parallel for
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			result[i] += matrix[ i * x + j ] * vector[j];
		}
	}
	}

	double end = omp_get_wtime();

	for (int i = 0; i < y; i++)
	{
//		cout << result[i] << endl;
	}

	cout << end - start << endl;

	delete[] matrix;
	delete[] vector;
	delete[] result;
}

	return 0;
}
