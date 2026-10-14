calc.out: main.o stack.o parser.o functions.o counter.o error.o stack.h types.h functions.h parser.h counter.h const.h main.h
	gcc -g -o calc.out main.o functions.o stack.o parser.o error.o counter.o -lm

main.o: main.c functions.o stack.h types.h functions.h parser.h counter.h error.o
	gcc -c -g -o main.o main.c

stack.o: stack.c types.h 
	gcc -c -g -o stack.o stack.c

functions.o: functions.c const.h types.h parser.h
	gcc -c -g -o functions.o functions.c

parser.o: parser.c const.h functions.h types.h main.h
	gcc -c -g -o parser.o parser.c -lm

counter.o: counter.c stack.h
	gcc -c -g -o counter.o counter.c -lm

error.o: error.c const.h
	gcc -c -g -o error.o error.c
