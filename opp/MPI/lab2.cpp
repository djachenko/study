#include <mpi.h>
#include <fstream>
#include <iostream>

#include "MPI_Matrix.h"

#define comm MPI_COMM_WORLD

using namespace std;

float squareNorm(const Matrix & matrix)
{
	float result = 0;
	
	for (int i = 0; i < matrix.height(); i++)
	{
		result += matrix[i][0] * matrix[i][0];
	}

	return result;
}

int main(int argc, char ** argv)
{
	MPI_Init(&argc, &argv);

	int size;
	int rank;

	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	ifstream sizeInput;
	sizeInput.open("sizes.txt");

	int width;
	int height;

	sizeInput >> width >> height;

	int div = height / size;
	int mod = height % size;

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

	ifstream matrixInput("matrix.bin", ios::binary);
	ifstream fInput("f.bin", ios::binary);

	double ** matrix = new double[blockSizes[rank]];
	
	for (int i = 
		
	matrixInput.seekg(width * offsets[rank] * sizeof(float), ios::beg);
	matrix.byteRead(matrixInput);//чтение матрицы

	MPI_Matrix f(1, height);
	f.byteRead(fInput);
	float fNorm = squareNorm(f);

	f = Matrix(1, blockSizes[rank]);
	fInput.seekg(offsets[rank] * sizeof(float), ios::beg);
	f.byteRead(fInput);//и правой части

	MPI_Matrix step;
	MPI_Matrix x(1, width);
	MPI_Matrix result(1, blockSizes[rank]);

	float tau = 0.01;
	float epsilon = 0.0000001;

	//matrix.print();

	for (int i = 0; ; i++)
	{
		step = matrix * x - f;

		for (int j = 0; j < result.height(); j++)
		{
			result[j][0] = x[j][0] - step[j][0] * tau;//step
		}

		//printf("rank: %d result: %d %d\n", rank, result.height(), result.width() );

		//cin.get();

		for (int j = 0; j < result.height(); j++)
		{
			printf("%d %d: %f\n", rank, j, result[j][0]);
		}

		MPI_Barrier(comm);

		MPI_Matrix::allGatherV(result, x, blockSizes, offsets);//update x

		if ( squareNorm(step) / fNorm < epsilon)
		{
			float currSum = squareNorm(step);
			float sum = 0;

			MPI_Barrier(comm);

			cout << "start";

			MPI_Allreduce(&currSum, &sum, 1, MPI_FLOAT, MPI_SUM, comm);

			MPI_Barrier(comm);

			cout << "finish";

			if (sum / fNorm < epsilon)
			{
				break;
			}
		}
	}

	cout << "out" << endl;

	if (0 == rank)
	{
		x.print();
	}

	MPI_Finalize();

	delete[] blockSizes;
	delete[] offsets;

	return 0;
}
