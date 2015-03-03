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

	MPI_Matrix matrix(x, blockSizes[rank]);
	MPI_Matrix vector(1, x);

	ifstream matrixInput("matrix.bin", ios::binary);
	ifstream vectorInput("vector.bin", ios::binary);
	
	matrixInput.seekg(x * offsets[rank] * sizeof(float), ios::beg);

	matrix.byteRead(matrixInput);
	vector.byteRead(vectorInput);

	MPI_Matrix result = matrix * vector;

	MPI_Matrix gathering = MPI_Matrix(1, y);

	MPI_Matrix::allGatherV(result, gathering, blockSizes, offsets);

	MPI_Barrier(comm);

	if (0 == rank)
	{
		gathering.print();
	}

	MPI_Finalize();

	delete[] blockSizes;
	delete[] offsets;

	return 0;
}
