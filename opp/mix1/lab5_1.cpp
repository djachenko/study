#include <mpi.h>
#include <fstream>
#include <iostream>

#include "MPI_Matrix.h"

#define comm MPI_COMM_WORLD

using namespace std;

int main(int argc, char ** argv)
{
	MPI_Init(&argc, &argv);

	int size;
	int rank;

	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	ifstream sizeInput;
	sizeInput.open("sizes.txt");

	int x;
	int y;

	sizeInput >> x >> y;

	int div = y / size;
	int mod = y % size;

	int * blockSizes = new int[size];
	int * offsets = new int[size];

	for (int i = 0; i < mod; i++)
	{
		blockSizes[i] = div + 1;
	}

	for (int i = mod; i < size; i++)
	{
		blockSizes[i] = div;
	}

	offsets[0] = 0;

	for (int i = 1; i < size; i++)
	{
		offsets[i] = offsets[i-1] + blockSizes[i-1];
	}

	double * matrix = new double[ x * blockSizes[rank] ];
	double * vector = new double[ x ];

	ifstream matrixInput("matrix.bin", ios::binary);
	ifstream vectorInput("vector.bin", ios::binary);
	
	matrixInput.seekg(x * offsets[rank] * sizeof(float), ios::beg);

	matrixInput.read((char*)matrix, x * blockSizes[rank] * sizeof(*matrix));
	vectorInput.read((char*)vector, x * sizeof(*vector));

	double * result = new double[ blockSizes[rank] ];
	
	#pragma omp parallel
	for (int i = 0; i < blockSizes[rank]; i++)
	{
		double tempResult;

		#pragma omp for reduction ( + : tempResult )
		for (int j = 0; j < y; j++)
		{
			tempResult += matrix[ i * x + j ] * vector[j];
		}

		result[i] = tempResult
	}

	double * gathering = new double[ y ];

	MPI_Allgatherv(result, blockSizes[rank], MPI_DOUBLE, gathering, blockSizes, offsets, MPI_DOUBLE, comm);

	if (0 == rank)
	{
		for (int i = 0; i < y; i++)
		{
			cout << gathering[i] << endl;
		}
	 }

	MPI_Finalize();

	delete[] blockSizes;
	delete[] offsets;

	return 0;
}
