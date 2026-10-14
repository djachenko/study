#include <mpi.h>

#include "MPI_Matrix.h"

MPI_Matrix::MPI_Matrix()
:Matrix()
{
}

MPI_Matrix::MPI_Matrix(int x, int y)
:Matrix(x, y)
{
}

MPI_Matrix::MPI_Matrix(const Matrix& other)
:Matrix(other)
{
}

MPI_Matrix::~MPI_Matrix()
{
}

void MPI_Matrix::send(int process, MPI_Comm comm)
{
	int x = this->width();
	int y = this->height();

	MPI_Send(&x, 1, MPI_INT, process, 118, comm);
	MPI_Send(&y, 1, MPI_INT, process, 119, comm);

	MPI_Send(*(*this), x*y, MPI_FLOAT, process, 117, comm);
}

void MPI_Matrix::receive(int process, MPI_Comm comm)
{
	MPI_Status *status = NULL;

	int x = 0;
	int y = 0;

	MPI_Recv(&x, 1, MPI_INT, 0, 118, MPI_COMM_WORLD, status);
	MPI_Recv(&y, 1, MPI_INT, 0, 119, MPI_COMM_WORLD, status);

	this->setTable(x, y);

	MPI_Recv(*(*this), x*y, MPI_FLOAT, 0, 117, MPI_COMM_WORLD, status);
}

void MPI_Matrix::allGatherV(Matrix & sendMatrix, Matrix & receiveMatrix, int * receiveCounts, int * offsets, MPI_Comm comm)
{
	MPI_Allgatherv(*sendMatrix, sendMatrix.width() * sendMatrix.height(), MPI_FLOAT, *receiveMatrix, receiveCounts, offsets, MPI_FLOAT, comm);
}

void MPI_Matrix::allReduce(Matrix & source, Matrix & destination, MPI_Op op, MPI_Comm comm)
{
	MPI_Allreduce(*source, *destination, source.height() * source.width(), MPI_FLOAT, op, comm);
}
