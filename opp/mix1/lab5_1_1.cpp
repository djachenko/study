#include <mpi.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

#define comm MPI_COMM_WORLD
#define N 1024

using namespace std;

int main(int argc, char ** argv)
{
	MPI_Init(&argc, &argv);

	int size;
	int rank;

	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	int div = N / size;
	int mod = N % size;

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

	double * matrix = new double[ N * blockSizes[rank] ];
	double * vector = new double[ N ];

	srand(time(NULL));

	for (int i = 0; i < blockSizes[rank]; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrix[ i * N + j ] = rand() % 1000;
		}
	}

	for (int i = 0; i < N; i++)
	{
		vector[i] = rand() % 1000;
	}

	double * result = new double[ blockSizes[rank] ];

	for (int threads = 1; threads <= 8; threads++)
	{
		omp_set_num_threads(threads);

		double start = omp_get_wtime();

		#pragma omp parallel for
		for (int i = 0; i < blockSizes[rank]; i++)
		{
			result[i] = 0;

			for (int j = 0; j < N; j++)
			{
				result[i] += matrix[ i * N + j ] * vector[j];
			}
		}

		double end = omp_get_wtime();

		double * gathering = new double[ N ];

		MPI_Allgatherv(result, blockSizes[rank], MPI_DOUBLE, gathering, blockSizes, offsets, MPI_DOUBLE, comm);

		if (0 == rank)
		{
			for (int i = 0; i < N; i++)
			{
	//			cout << gathering[i] << endl;
			}
		}

		printf("time %lf from with %d threaded process #%d of %d\n", end - start, threads, rank, size);

		MPI_Barrier(comm);

		if (0 == rank)
		{
			cout << endl;
		}
	}

	MPI_Finalize();

	delete[] blockSizes;
	delete[] offsets;

	return 0;
}
