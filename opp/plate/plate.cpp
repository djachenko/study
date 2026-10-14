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

	double Dx = 10;
	double Dy = 5;

	int Nx = 10;
	int Ny = 5;

	int M = Nx * Ny;

	int div = M / size;
	int mod = M % size;
	
	int * blockSizes = new int[size];

	for (int i = 0; i < mod; i++)
	{
		blockSizes[i] = div + 1;
	}

	for (int i = mod; i < size; i++)
	{
		blockSizes[i] = div;
	}

	double * A = new double[ M * blockSizes[rank] ];
	double * f = new double[ blockSizes[rank] ];

	double hx = Dx / (Nx - 1);
	double hy = Dy / (Ny - 1); 

	double a = -1 * (2.0 / (hx * hx) + 2.0 / (hy * hy));
	double b = 1.0 / (hx * hx);
	double c = 1.0 / (hy * hy); 

	for (int i = 0; i < M; i++)
	{
		if ( i % size == rank )
		{
			int line = i / size;

			for (int j = 0; j < M; j++)
			{
				A[line * M + j] = 0;

				if (i == j)
				{
					A[line * M + j] = a;
				}

				if (j == i + 1  && j % Nx != 0)//not the first column in block
				{
					A[line * M + j] = b;
				}

				if (j == i - 1 && (j + 1) % Nx != 0)//not the last
				{
					A[line * M + j] = b;
				}

				if (j == i + Nx)
				{
					A[line * M + j] = c;
				}

				if (j == i - Nx)
				{
					A[line * M + j] = c;
				}
			}
		}
	}

	{
		//First kind

		int x;
		int y;

		double L = 10000000;

		A[ x * Nx + y ] = L;
		f[ x * Nx + y ] = U * L;
	}

	{
		//Second kind

	}


	double epsilon = 0.001;
	double * transport = new double[ M + 1 ];

	struct timeval start;

	gettimeofday(&start, NULL);

	for (int i = 0; i < M; i++)
	{
		if (0 == rank && i % 10 == 0)
		{
			printf("%d ", i);
		}

		int root = i % size;

		if (rank == root)
		{
			memcpy(transport, A + (i / size) * M, M * sizeof(*A));
			transport[ M ] = f[ i / size ];
		}

		MPI_Bcast(transport, M + 1, MPI_DOUBLE, root, comm);
		double currentResult = transport[ M ];

		for (int j = i + 1; j < M; j++)
		{
			if ( j % size == rank )
			{
				double alpha = A[ (j / size) * M + i ] / transport[i];
				int line = j / size;

				for (int k = i; k < M; k++)
				{
					A[ line * M + k ] -= transport[k] * alpha;

					if (A[ line* M + k ] * A[ line * M + k ] < epsilon)
					{
						A[ line * M + k ] = 0;
					}
				}

				f[ line ] -= currentResult * alpha;
			}
		}
		
		if (0 == rank && i % 10 == 0)
		{
			printf("%d\n", i);
		}
	}

	MPI_Barrier(comm);

	for (int i = M - 1; i >= 0; i--)
	{
		int root = i % size;
		
		double transportDiag = 0;
		double transportResult = 0;

		if (rank == root)
		{
			transportDiag = A[ (i / size) * M + i ];
			transportResult = f[ i / size ];
		}

		MPI_Bcast(&transportResult, 1, MPI_DOUBLE, root, comm);
		MPI_Bcast(&transportDiag, 1, MPI_DOUBLE, root, comm);

		for (int j = i - 1; j >= 0; j--)
		{
			if (j % size == rank)
			{
				double alpha = A[ (j / size) * M + i] / transportDiag;

				f[ j / size ] -= transportResult * alpha;
			}
		}
	}

	struct timeval end;

	gettimeofday(&end, NULL);

	for (int i = 0; i < M; i++)
	{
		if ( i % size == rank)
		{
			f[ i / size ] /= A[ (i / size) * M + i ];
		}
	}

	double * finalResult = new double[ M ];

	for (int i = 0; i < M; i++)
	{
		double transportResult = 0;

		if (i % size == rank)
		{
			transportResult = f[ i / size ];
		}

		MPI_Bcast(&transportResult, 1, MPI_DOUBLE, i % size, comm);

		finalResult[i] = transportResult;
	}

	MPI_Barrier(comm);

	if (0 == rank)
	{
		ofstream output("out.bin", ofstream::binary);

		output.write((char*)finalResult, M * sizeof(*finalResult));
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
	delete[] transport;

	delete[] A;
	delete[] f;
	delete[] finalResult;
	
	return 0;
}
