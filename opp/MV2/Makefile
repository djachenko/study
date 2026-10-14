all: lab1_2.out

lab1_2.out: Matrix.o MPI_Matrix.o lab1_2.o 
	mpicxx -o lab1_2.out Matrix.o MPI_Matrix.o lab1_2.o

MPI_Matrix.o: MPI_Matrix.cpp MPI_Matrix.h Matrix.h Matrix.cpp
	mpicxx -c -o MPI_Matrix.o MPI_Matrix.cpp

Matrix.o: Matrix.cpp Matrix.h
	mpicxx -c -o Matrix.o Matrix.cpp

lab1_2.o: lab1_2.cpp MPI_Matrix.h
	mpicxx -c -o lab1_2.o lab1_2.cpp

clean:
	rm *.o *.out

gen: generator
	./generator.out

generator: generator.cpp
	g++ -o generator.out generator.cpp
