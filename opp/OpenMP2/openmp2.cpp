#include <omp.h>
#include <fstream>
#include <iostream>
#include <iomanip>

#define comm MPI_COMM_WORLD

using namespace std;

double squareNorm(double * matrix, int size)
{
	double nextX = 0;
	
	for (int i = 0; i < size; i++)
	{
		nextX += matrix[i] * matrix[i];
	}

	return nextX;
}

int main(int argc, char ** argv)
{
	for (int threads = 1; threads <= 16; threads++)
	{
		omp_set_num_threads(threads);

		ifstream sizeInput;
		sizeInput.open("sizes.txt");

		int size;

		sizeInput >> size;

		ifstream matrixInput("matrix.bin", ios::binary);
		ifstream fInput("f.bin", ios::binary);
		
		double * matrix = new double[ size * size ];
		double * f = new double[size];

		matrixInput.read((char*)matrix, size * size * sizeof(*matrix));
		fInput.read((char*)f, 1 * size * sizeof(*f));

		double fNorm = squareNorm(f, size);

		double * step = new double[size];
		double * x = new double[size];
		double * nextX = new double[size];

		double tau = 0.01;
		double epsilon = 0.0000001;

		for (int i = 0; i < size; i++)
		{
			x[i] = 0.6;
			step[i] = 0;
		}

		double start = omp_get_wtime();

		#pragma omp parallel
		for ( bool flag = true; flag;  )
		{
			#pragma omp for
			for (int i = 0; i < size; i++)
			{
				step[i] = -f[i];

				for (int j = 0; j < size; j++)
				{
					step[i] += matrix[ i * size + j ] * x[j];
				}
			}

			#pragma omp for
			for (int j = 0; j < size; j++)
			{
				x[j] -= step[j] * tau;//step
			}

			#pragma omp barrier
		
			if ( squareNorm(step, size) / fNorm < epsilon)
			{
				flag = false;
			}

		//	printf("count: %d\n", count);
		}
			
		double end = omp_get_wtime();

		for (int i = 0; i < size; i++)
		{
	//		cout << x[i] << endl;
		}

		cout << end - start << endl;

		delete[] step;
		delete[] x;
		delete[] nextX;
		delete[] matrix;
		delete[] f;
	}

	return 0;
}
