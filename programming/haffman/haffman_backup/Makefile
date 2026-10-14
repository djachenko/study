main.out: main.o archiver.o dearchiver.o list.o tree.o functions.o
	gcc -g -o main.out main.o archiver.o list.o tree.o functions.o dearchiver.o

list.o: list.c types.h
	gcc -g -c -o list.o list.c

tree.o: tree.c types.h
	gcc -g -c -o tree.o tree.c

functions.o: functions.c const.h
	gcc -g -c -o functions.o functions.c

archiver.o: archiver.c list.o tree.o const.h types.h
	gcc -g -c -o archiver.o archiver.c

dearchiver.o: dearchiver.c list.o tree.o const.h types.h
	gcc -g -c -o dearchiver.o dearchiver.c

main.o: main.c archiver.o tree.o types.h
	gcc -g -c -o main.o main.c
