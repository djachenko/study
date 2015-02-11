main.out: tree.o main.o list.o encoder.o archiver.o
	gcc -g -o main.out tree.o main.o list.o encoder.o archiver.o

main.o: main.c types.h list.o tree.o
	gcc -g -c -o main.o main.c

tree.o: tree.c types.h
	gcc -g -c -o tree.o tree.c

encoder.o: encoder.c list.o types.h const.h
	gcc -g -c -o encoder.o encoder.c

list.o: list.c types.h
	gcc -g -c -o list.o list.c

archiver.o: archiver.c list.o
	gcc -g -c -o archiver.o archiver.c 
