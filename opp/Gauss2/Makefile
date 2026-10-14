NAME = gauss2

all: $(NAME).out

$(NAME).out: $(NAME).cpp
	mpecc -mpicc=mpicxx -mpilog -o $(NAME).out $(NAME).cpp

Matrix.o: Matrix.cpp Matrix.h
	mpicxx -c -o Matrix.o Matrix.cpp

clean:
	rm *.o *.out *.bin *.txt

gen: generator
	./generator.out

generator.o: generator.cpp Matrix.h
	g++ -c -o generator.o generator.cpp

generator: generator.o Matrix.o
	g++ -o generator.out generator.o Matrix.o
