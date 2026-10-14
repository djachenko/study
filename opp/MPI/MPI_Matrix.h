#ifndef MPI_Matrix_h
#define MPI_Matrix_h

#include <mpi.h>
#include "Matrix.h"

class MPI_Matrix: public Matrix
{
public:
	MPI_Matrix();
	MPI_Matrix(int x, int y);
	MPI_Matrix(const Matrix& other);

	~MPI_Matrix();

	void send(int process, MPI_Comm comm = MPI_COMM_WORLD);
	void receive(int process, MPI_Comm comm = MPI_COMM_WORLD);

	static void allGatherV(Matrix & sendMatrix, Matrix & receiveMatrix, int * receiveCounts, int * offsets, MPI_Comm comm = MPI_COMM_WORLD);
	static void allReduce(Matrix & source, Matrix & destination, MPI_Op op, MPI_Comm comm = MPI_COMM_WORLD);
};

#endif//MPI_Matrix_h
