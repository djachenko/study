#include <mpi.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <fstream>

#define comm MPI_COMM_WORLD

using namespace std;

double abs(double a)
{
	if (a > 0)
	{
		return a;
	}
	else
	{
		return -a;
	}
}

MPI_Request send_bottom(double * cell, int sizeX, int sizeY, int dest)
{
	MPI_Request request;

	MPI_Isend(&cell[sizeY * (sizeX + 2) + 1], sizeX, MPI_DOUBLE, dest, 117, comm, &request);//send bottom

	return request;
}

MPI_Request send_top(double * cell, int sizeX, int sizeY, int dest)
{
	MPI_Request request;

	MPI_Isend(&cell[1 * (sizeX + 2) + 1], sizeX, MPI_DOUBLE, dest, 118, comm, &request);//send top

	return request;
}

MPI_Request receive_bottom(double * cell, int sizeX, int sizeY, int source) 
{
	MPI_Request request;

	MPI_Irecv(&cell[(sizeY + 1) * (sizeX + 2) + 1], sizeX, MPI_DOUBLE, source, 118, comm, &request);//receive other's top and store to bottom edge

	return request;
}

MPI_Request receive_top(double * cell, int sizeX, int sizeY, int source)
{
	MPI_Request request;

	MPI_Irecv(&cell[1], sizeX, MPI_DOUBLE, source, 117, comm, &request);//receive other's bottom and store to top edge

	return request;
}

int main(int argc, char * argv[])
{
	MPI_Init(&argc, &argv);

	double Dx = 10;
	double Dy = 5;

	int Nx = 100;
	int Ny = 50;
	
	double hx = Dx / (Nx - 1);
	double hy = Dy / (Ny - 1); 

	int size;
	int rank;

	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	int div = Ny / size;
	int mod = Ny % size;

	int * blockSizes = new int[size];

	for (int i = 0; i < mod; i++)
	{
		blockSizes[i] = div + 1;
	}

	for (int i = mod; i < size; i++)
	{
		blockSizes[i] = div;
	}

	int sizeX = Nx;
	int sizeY = blockSizes[rank];

	int square = (sizeX + 2) * (sizeY + 2);

	double * cell = new double[ square ];
	double * oldCell = new double[ square ];
	double * f = new double[ square ];
	double * values = new double[ square ];

	double epsilon = 0.000001;

	double * maxes = new double[size];
	
	memset(oldCell, 0, square);

	for (int i = 1; i <= sizeY; i++)
	{
		oldCell[ i * (sizeX + 2) + sizeX + 1] = 1;
		cell[ i * (sizeX + 2) + sizeX + 1] = 1;
	}

	{
		int offset = 0;
		int root = 0;

		for ( ; ; )
		{
			offset += blockSizes[root];

			if (offset > Ny / 2)
			{
				offset -= blockSizes[root];

				break;
			}
			else
			{
				root++;
			}
		}

		if (rank == root)
		{
			f[ (Ny / 2 - offset) * (sizeX + 2) + Nx / 4 ] = 250;
			f[ (Ny / 2 - offset) * (sizeX + 2) + 3 * Nx / 4 ] = -250;
		}
	}

	struct timeval start;
	gettimeofday(&start, NULL);

	for (int iteration = 0; ; iteration++)
	{
		//start iteration

		MPI_Request top_send;
		MPI_Request bottom_send;

		MPI_Request top_receive;
		MPI_Request bottom_receive;

		if (rank != 0)
		{
			top_send = send_top(oldCell, sizeX, sizeY, rank - 1);
			top_receive = receive_top(oldCell, sizeX, sizeY, rank - 1);
		}

		if (rank != size - 1)
		{
			bottom_send = send_bottom(oldCell, sizeX, sizeY, rank + 1);
			bottom_receive = receive_bottom(oldCell, sizeX, sizeY, rank + 1);
		}

		double max = 0;

		for (int i = 2; i <= sizeY - 1; i++)
		{
			for (int j = 1; j <= sizeX; j++)
			{
				int index = i * (sizeX + 2) + j;

				if (j == 1)
				{
					cell[index] = oldCell[index + 1];
				}
				else
				{
					cell[ index ] = (1.0 / ( 2.0 / ( hx * hx ) + 2.0 / ( hy * hy ) ) ) * ( ( oldCell[ index - 1 ] + oldCell[ index + 1 ] ) / (hx * hx) + (oldCell[(i - 1) * (sizeX + 2) + j] + oldCell[(i + 1) * (sizeX + 2) + j]) / (hy * hy) + f[ index ] );//Jacobi
				}

				double d = abs(cell[ index ] - oldCell[ index ]);

				if (d > max)
				{
					max = d;
				}
			}
		}

		MPI_Status status;

		if (rank != 0)
		{
			MPI_Wait(&top_receive, &status);
		}
		
		for (int j = 1; j <= sizeX; j++)
		{
			int i = 1;

			int index = i * (sizeX + 2) + j;

			if (rank == 0 && j != 1)
			{
				cell[ index ] = oldCell[ (i + 1) * (sizeX + 2) + j ] - 0.5;
			}
			else
			{
				if (j == 1)
				{
					cell[index] = oldCell[index + 1];
				}
				else
				{
					cell[ index ] = (1.0 / ( 2.0 / ( hx * hx ) + 2.0 / ( hy * hy ) ) ) * ( ( oldCell[ index - 1 ] + oldCell[ index + 1 ] ) / (hx * hx) + (oldCell[(i - 1) * (sizeX + 2) + j] + oldCell[(i + 1) * (sizeX + 2) + j]) / (hy * hy) + f[ index ] );//Jacobi
				}
			}

			double d = abs(cell[ index ] - oldCell[ index ]);

			if (d > max)
			{
				max = d;
			}
		}

		if (rank != size - 1)
		{
			MPI_Wait(&bottom_receive, &status);
		}

		for (int j = 1; j <= sizeX; j++)
		{
			int i = sizeY;

			int index = i * (sizeX + 2) + j;

			if (rank == size - 1 && j != 1)
			{
				cell[ index ] = oldCell[ (i - 1) * (sizeX + 2) + j ];
			}
			else
			{
				if (j == 1)
				{
					cell[index] = oldCell[index + 1];
				}
				else
				{
					cell[ index ] = (1.0 / ( 2.0 / ( hx * hx ) + 2.0 / ( hy * hy ) ) ) * ( ( oldCell[ index - 1 ] + oldCell[ index + 1 ] ) / (hx * hx) + (oldCell[(i - 1) * (sizeX + 2) + j] + oldCell[(i + 1) * (sizeX + 2) + j]) / (hy * hy) + f[ index ] );//Jacobi
				}
			}

			double d = abs(cell[ index ] - oldCell[ index ]);

			if (d > max)
			{
				max = d;
			}
		}

		//end iteration

		MPI_Allgather(&max, 1, MPI_DOUBLE, maxes, 1, MPI_DOUBLE, comm);

		max = maxes[0];

		for (int i = 0; i < size; i++)
		{
			if (maxes[i] > max)
			{
				max = maxes[i];
			}
		}

		if (max <= epsilon)
		{
			break;
		}

		double * temp = oldCell;
		oldCell = cell;
		cell = temp;
	}

	struct timeval end;
	gettimeofday(&end, NULL);

	for (int i = 0; i < size; i++)
	{
		MPI_Barrier(comm);

		if (i == rank)
		{
			cout << (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0 << endl;

			ofstream output;

			if (rank == 0)
			{
				output.open("out3.bin", ofstream::binary);
			}
			else
			{
				output.open("out3.bin", ofstream::binary | ofstream::app);
			}

			for (int j = 1; j <= sizeY; j++)
			{
				output.write((char *)&cell[ j * (sizeX + 2) + 1 ], sizeX * sizeof(*cell));
			}

			output.close();
		}
	}

	delete[] maxes;
	delete[] values;
	delete[] f;
	delete[] oldCell;
	delete[] cell;

	delete[] blockSizes;

	MPI_Finalize();

	return 0;
}
