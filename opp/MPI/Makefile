NAME = lab2_1

all: $(NAME).out

$(NAME).out: Matrix.o MPI_Matrix.o $(NAME).o
	mpicxx -o $(NAME).out Matrix.o MPI_Matrix.o $(NAME).o

MPI_Matrix.o: MPI_Matrix.cpp MPI_Matrix.h Matrix.h Matrix.cpp
	mpicxx -c -o MPI_Matrix.o MPI_Matrix.cpp

Matrix.o: Matrix.cpp Matrix.h
	mpicxx -c -o Matrix.o Matrix.cpp

$(NAME).o: $(NAME).cpp MPI_Matrix.h
	mpicxx -c -o $(NAME).o $(NAME).cpp

clean:
	rm *.o *.out *.bin *.txt

gen: generator
	./generator.out

generator.o: generator.cpp Matrix.h
	g++ -c -o generator.o generator.cpp

generator: generator.o Matrix.o
	g++ -o generator.out generator.o Matrix.o
