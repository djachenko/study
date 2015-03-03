NAME = openmp2
 
COMPILER = g++

all: $(NAME).out

$(NAME).out: $(NAME).cpp 
	$(COMPILER) -fopenmp -o $(NAME).out $(NAME).cpp

Matrix.o: Matrix.cpp
	$(COMPILER) -c Matrix.cpp

clean:
	rm *.o *.out *.bin *.txt

gen: generator
	./generator.out

generator: generator.o Matrix.o
	g++ -o generator.out generator.o Matrix.o

generator.o: generator.cpp Matrix.h
	g++ -c generator.cpp
