#include <mpi.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "vector_output.h"
#include "time_check.h"
#include "solve_system.h"
#include "matrix_class.h"

#define MCW MPI_COMM_WORLD
#define MASTER (rank == 0)

#define DEBUG false

// these variables are necessary for time checking
struct timeval tv1, tv2, dtv;
struct timezone tz;

// vector operations
void fill_vector( double *vector, double value, int size );
void copy_vector( double *src, double *dst, int size );

// the square of vector norm
double square_norm( double *vector, int size );

int main(int argc, char **argv) {
	MPI_Init( &argc, &argv );

	// MPI process data
	int size = 0;
	int rank = 0;

	MPI_Comm_size( MCW, &size );
	MPI_Comm_rank( MCW, &rank );

	// plate size
	double Dx = 10.0;
	double Dy = 5.0;
	
	// grid size
	int Nx = 100;
	int Ny = 50;

	// grid intervals
	double hx = 0;
	double hy = 0;
	
	// size of matrix, which will be used for solving this problem
	// will be calculated later
	int msize = 0;

	// matrix coefficients
	double a = 0;
	double b = 0;
	double c = 0;

	// scanning plate parameters
	if ( argc > 4 ) {
		sscanf(argv[1], "%lf", &Dx);
		sscanf(argv[2], "%lf", &Dy);
		sscanf(argv[3], "%d",  &Nx);
		sscanf(argv[4], "%d",  &Ny);
	} else {
		printf("Not enougn parameters! Using default values.\n");
	};

	msize = Nx * Ny;

	hx = Dx / (Nx - 1);
	hy = Dy / (Ny - 1);

	a = -( 2 / ( hx * hx ) + 2 / ( hy * hy ) );
	b = 1 / ( hx * hx );
	c = 1 / ( hy * hy );

	if ( DEBUG ) {
		printf("Plate size:    %.2lf x %.2lf\n", Dx, Dy);
		printf("Grid size:     %d x %d\n", Nx, Ny);
		printf("Grid interval: %.2lf x %.2lf\n", hx, hy);
		printf("Matrix size:   %d\n", msize);

		printf("a: %lf\n", a);
		printf("b: %lf\n", b);
		printf("c: %lf\n", c);
	}

	if ( size > msize ) {
		if ( rank == 0 ) {
			printf("ERROR: there are more processes than lines in matrix!\n");	
		}
		MPI_Finalize();
		return 0;
	}	

	int chunk_size = msize / size; 	// strings for each process
	int rest = msize % size; 		// the rest of strings
	int shift = chunk_size * rank; 	// the first string that current process should take

	// take one more string if matrix is not divisible by 'size'
	if ( rest != 0 ) {
		if ( rank < rest ) {
			shift += rank;
			chunk_size += 1;
		} else {
			shift += rest;	
		}
	}
	shift = 0;

	Matrix *matrix = new Matrix( msize, chunk_size, rank, size );

	//double *matrix    = (double*)malloc( sizeof(double) * matrix_length ); 	// part of the matrix for this process
	double *vector_f  = (double*)malloc( sizeof(double) * msize );			// f vector
	double *vector_t  = (double*)malloc( sizeof(double) * msize );			// t vector
	double *my_result = (double*)malloc( sizeof(double) * msize );			// local result of multiplication
	double *result    = (double*)malloc( sizeof(double) * msize );			// global result
	double *checksum  = (double*)malloc( sizeof(double) * msize );			// temp vector to calculate checksum
	double *v_temp    = (double*)malloc( sizeof(double) * msize );			// temp vector to calculate anything

	//memset( matrix, 0, sizeof(double) * matrix_length);

	memset( vector_f,  0, sizeof(double) * msize );
	memset( my_result, 0, sizeof(double) * msize );
	memset( result,    0, sizeof(double) * msize );
	memset( vector_t,  0, sizeof(double) * msize );
	memset( checksum,  0, sizeof(double) * msize );
	memset( v_temp,    0, sizeof(double) * msize );
	
	// fill matrix of the current process
	int line_counter = 0;
	for ( int i = 0; i < msize; ++i ) {
		if ( (i - rank) < 0 || (i - rank) % size != 0 )  {
			//printf("pr. %d passed %d \n", rank, i);
			continue;
		}

		//center 'a' diagonal
		matrix->set( line_counter, i, a );
		//matrix[ line_counter * width + i ] = a;
		// if not the first line of block
		if ( (i % Nx) != 0 ) {
			//matrix[ line_counter * width + i - 1 ] = b;
			matrix->set( line_counter, i - 1, b );
		}
		// if not the last line of block
		if ( ((i + 1) % Nx) != 0 ) {
			//matrix[ line_counter * width + i + 1 ] 	= b;
			matrix->set( line_counter, i + 1, b );
		}

		// left 'c' diagonal
		if ( (i - Nx) >= 0 ) {
			//matrix[ line_counter * width + i - Nx ] = c;
			matrix->set( line_counter, i - Nx, c );
		}
		// rignt 'c' diagonal
		if ( (i + Nx) < msize ) {
			//matrix[ line_counter * width + i + Nx ] = c;
			matrix->set( line_counter, i + Nx, c );
		}
		
		line_counter++;
	}

	// edge conditions
	// 1st kind
	vector_f[Ny*Nx/2 + Nx/2] = 10;
	vector_f[Nx*(Ny-2) + 5] = 15;
	vector_f[Nx*2 + 5] = -15;

	// 2nd kind
	for (int k = 0; k < Ny*Nx; k+= Nx) {
		vector_f[k] = 0.5;

		if ( matrix->hasLine(k) )  {
			matrix->setRow( ((k - rank) / size), 0 );
			matrix->setColumn( k, 0 );

			int real_index = (k - rank) / size;

			matrix->set( real_index, k, (1.0 / hx) );
			if ( k - 1 > 0 ){
				matrix->set( real_index, k - 1, (-1.0 / hx) );	
			}
			
		}

		if ( matrix->hasLine(k - 1) )  {
			int real_index = (k - 1 - rank) / size;

			matrix->set( real_index, k, (-1.0 / hx) );	
		}
	}	

	line_counter = 0;
	for ( int i = 0; i < msize; ++i ) {
		if ( (i - rank) < 0 || (i - rank) % size != 0 )  {
			//printf("pr. %d passed %d \n", rank, i);
			continue;
		}

		//matrix[ line_counter * width + msize ] = vector_f[i];
		matrix->setRightValue( line_counter, vector_f[i] );
		line_counter++;
	}


	
	if (rank == 0) {
		for ( int i = 0; i < chunk_size && i < 20; ++i ) {
			//print_vector(matrix + width * i, 20);
		}
	}

	time_start();

	solve_system( matrix->getPointer(), msize, chunk_size, rank, size );


	line_counter = rank;
	for ( int i = 0; i < chunk_size; i++ ) {
		//my_result[line_counter] = matrix[i * width + msize];
		my_result[line_counter] = matrix->getRightValue(i);
		line_counter += size;
	}

	MPI_Allreduce( my_result, result, msize, MPI_DOUBLE, MPI_SUM, MCW );

	// if ( MASTER ) {
	// 	printf("result:\n");
	// 	print_vector( result, msize);	
	// }

	if ( MASTER ) {
		FILE * out_file = fopen("result_cluster.bin", "w");
		fwrite(result, sizeof(double), msize, out_file);
		if ( DEBUG ) {
			printf("Written to file\n" );
		}
	}

	double timeTaken = time_stop();

	if ( rank == 0 ) printf("time taken: %lf s.\n", timeTaken);

	//free( matrix );
	free( vector_f );
	free( vector_t );
	free( my_result );
	free( result );
	free( checksum );
	free( v_temp );
	
	MPI_Finalize();

	return 0;	
}

double square_norm( double *vector, int size ) {
	double result = 0;

	for ( int i = 0; i < size; i++ ) {
		result += vector[i] * vector[i];
	}
	return result;
}
