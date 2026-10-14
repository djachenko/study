#include <mpi.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <cstring>

#define comm MPI_COMM_WORLD

using namespace std;

int main(int argc, char ** argv)
{
	MPI_Init(&argc, &argv);

	int size;
	int rank;

	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	ifstream sizeInput("sizes.txt");

	int x;
	int y;

	sizeInput >> x >> y;

	int div = y / size;
	int mod = x % size;
	
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
	double * result = new double[ blockSizes[rank] ];

	ifstream matrixInput("matrix.bin", ios::binary);
	ifstream resultInput("result.bin", ios::binary);

	matrixInput.seekg(x * offsets[rank] * sizeof(*matrix), ios::beg);
	matrixInput.read((char*)matrix, x * blockSizes[rank] * sizeof(*matrix));

	resultInput.seekg(1 * offsets[rank] * sizeof(*result), ios::beg);
	resultInput.read((char*)result, blockSizes[rank] * sizeof(*result));
	
	double epsilon = 0.001;

	int bufferSize = 1024 * 1024 * 128;
	double * buffer = new double[bufferSize];

	MPI_Buffer_attach(buffer, bufferSize * sizeof(*buffer) ); //bufferSize * sizeof(*buffer));

	double * current = new double[x+1];

	struct timeval start;
	gettimeofday(&start, NULL);

	for (int i = 0; i < y; i++)
	{
		int root;

		for (root = 0; i > offsets[root] + blockSizes[root] - 1; root++)//counting  root process (unique for every line)
		{
		}

		if (rank == root)
		{
			memcpy(current, matrix + (i - offsets[root]) * x, x * sizeof(*matrix));;
			current[x] = result[ i - offsets[root] ];
				
			for (int j = rank + 1; j < size; j++)
			{
				MPI_Send(current, x + 1, MPI_DOUBLE, j, 117, comm);
			}
		}
		else
		{
			if (rank > root)
			{
				MPI_Status status;

				MPI_Recv(current, x + 1, MPI_DOUBLE, root, 117, comm, &status);
			}
		}
	
		double currentResult = current[x];

		for (int j = i + 1; j < y; j++)
		{
			if (j >= offsets[rank] && j < offsets[rank] + blockSizes[rank])
			{
				double alpha = matrix[ (j - offsets[rank]) * x + i ] / current[i];

				for (int k = i; k < x; k++)
				{
					matrix[ (j - offsets[rank]) * x + k ] -= current[k] * alpha;

					if (matrix[ (j - offsets[rank]) * x + k ] * matrix[ (j - offsets[rank]) * x + k ] < epsilon)
					{
						matrix[ (j - offsets[rank]) * x + k ] = 0;
					}
				}

				result[ j - offsets[rank] ] -= currentResult * alpha;
			}
		}
	}

	for (int i = y - 1; i >= 0; i--)
	{
		int root;

		for (root = 0; i > offsets[root] + blockSizes[root] - 1; root++)//counting  root process (unique for every line)
		{
		}

		if (rank == root)
		{
			memcpy(current, matrix + (i - offsets[root]) * x, x * sizeof(*matrix));;
			current[x] = result[ i - offsets[root] ];

			for (int j = rank - 1; j >= 0; j--)
			{
				MPI_Bsend(current, x + 1, MPI_DOUBLE, j, 117, comm);
			}
		}
		else
		{
			if (rank < root)
			{
				MPI_Status status;
		
				MPI_Recv(current, x + 1, MPI_DOUBLE, root, 117, comm, &status);
			}
		}
	
		double currentResult = current[x];

		for (int j = i - 1; j >= 0; j--)
		{
			if (j >= offsets[rank] && j < offsets[rank] + blockSizes[rank])
			{
				double alpha = matrix[ (j - offsets[rank]) * x + i] / current[i];

				result[ j - offsets[rank] ] -= currentResult * alpha;
			}
		}
	}

	struct timeval end;

	gettimeofday(&end, NULL);

	for (int i = 0; i < y; i++)
	{
		if (i >= offsets[rank] && i < offsets[rank] + blockSizes[rank])
		{
			result[ i - offsets[rank] ] /= matrix[ (i - offsets[rank]) * x + i ];
		}
	}

	double * finalResult = new double[y];

	MPI_Allgatherv(result, blockSizes[rank], MPI_DOUBLE, finalResult, blockSizes, offsets, MPI_DOUBLE, comm);

	if (0 == rank)
	{
		for (int i = 0; i < y; i++)
		{
//			cout << finalResult[i] << endl;
		}
	}

	for (int i = 0; i < size; i++)
	{
		MPI_Barrier(comm);

		if (i == rank)
		{
			cout << (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0 << endl;
		}
	}

	MPI_Finalize();

	delete[] buffer;

	delete[] blockSizes;
	delete[] offsets;
	delete[] current;

	delete[] matrix;
	delete[] result;
	delete[] finalResult;
	
	return 0;
}
