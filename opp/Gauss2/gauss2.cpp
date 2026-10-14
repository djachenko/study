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

	ifstream sizeInput;
	sizeInput.open("sizes.txt");

	int x;
	int y;

	sizeInput >> x >> y;

	int div = y / size;
	int mod = x % size;
	
	int * blockSizes = new int[size];

	for (int i = 0; i < mod; i++)
	{
		blockSizes[i] = div + 1;

	}

	for (int i = mod; i < size; i++)
	{
		blockSizes[i] = div;
	}

	double * matrix = new double[ x * blockSizes[rank] ];
	double * result = new double[ blockSizes[rank] ];

	double * currentHook = new double[x+1];

	ifstream matrixInput("matrix.bin", ios::binary);
	ifstream resultInput("result.bin", ios::binary);

	for (int i = 0; i < y; i++)
	{
		if ( i % size == rank )
		{
			matrixInput.seekg(x * i * sizeof(*matrix), ios::beg);
			matrixInput.read((char*)(matrix + x * (i / size)), x * sizeof(*matrix));

			resultInput.seekg(1 * i * sizeof(*result), ios::beg);
			resultInput.read((char*)(result + 1 * (i / size)), 1 * sizeof(*result));
		}
	}

	double epsilon = 0.001;

	struct timeval start;

	gettimeofday(&start, NULL);

	for (int i = 0; i < y; i++)
	{
		int root = i % size;

		double * current = NULL;
		double currentResult = 0;

		current = currentHook; 

		if (rank == root)
		{
			memcpy(current, matrix + (i / size) * x, x * sizeof(*matrix));;
			current[x] = result[ i / size ];
		}

		MPI_Bcast(current, x + 1, MPI_DOUBLE, root, comm);
		currentResult = current[x];

		for (int j = i + 1; j < y; j++)
		{
			if ( j % size == rank )
			{
				double alpha = matrix[ (j / size) * x + i ] / current[i];

				for (int k = i; k < x; k++)
				{
					matrix[ (j / size) * x + k ] -= current[k] * alpha;

					if (matrix[ (j / size) * x + k ] * matrix[ (j / size) * x + k ] < epsilon)
					{
						matrix[ (j / size) * x + k ] = 0;
					}
				}

				result[ j / size ] -= currentResult * alpha;
			}
		}
	}

	MPI_Barrier(comm);

	for (int i = y - 1; i >= 0; i--)
	{
		int root = i % size;
		
		double current = 0;
		double currentResult = 0;

		if (rank == root)
		{
			current = matrix[ (i / size) * x + i ];
			currentResult = result[ i / size ];
		}

		MPI_Bcast(&currentResult, 1, MPI_DOUBLE, root, comm);
		MPI_Bcast(&current, 1, MPI_DOUBLE, root, comm);

		for (int j = i - 1; j >= 0; j--)
		{
			if (j % size == rank)
			{
				double alpha = matrix[ (j / size) * x + i] / current;

				result[ j / size ] -= currentResult * alpha;
			}
		}
	}

	struct timeval end;

	gettimeofday(&end, NULL);

	for (int i = 0; i < y; i++)
	{
		if ( i % size == rank)
		{
			result[ i / size ] /= matrix[ (i / size) * x + i ];
		}
	}

	double * finalResult = new double[y];

	printf("End2\n");

	for (int i = 0; i < y; i++)
	{
		double currentResult = 0;

		if (i % size == rank)
		{
			currentResult = result[ i / size ];
		}

		MPI_Bcast(&currentResult, 1, MPI_DOUBLE, i % size, comm);

		finalResult[i] = currentResult;
	}

	MPI_Barrier(comm);

	if (0 == rank)
	{

		for (int i = 0; i < y; i++)
		{
		//	cout << finalResult[i] << endl;
		}

//		cout << "size: " << size << endl;
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

	delete[] blockSizes;
	delete[] currentHook;

	delete[] matrix;
	delete[] result;
	delete[] finalResult;
	
	return 0;
}
