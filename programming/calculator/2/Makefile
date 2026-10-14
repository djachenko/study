calc.out: main.o stack.o parser.o functions.o counter.o stack.h types.h functions.h parser.h counter.h const.h
	gcc -o calc.out main.o functions.o stack.o parser.o counter.o -lm

main.o: main.c functions.o stack.h types.h functions.h parser.h counter.h
	gcc -c -o main.o main.c

stack.o: stack.c types.h
	gcc -c -o stack.o stack.c

functions.o: functions.c const.h types.h
	gcc -c -o functions.o functions.c

parser.o: parser.c const.h functions.h types.h
	gcc -c -o parser.o parser.c -lm

counter.o: counter.c stack.h
	gcc -c -o counter.o counter.c -lm
