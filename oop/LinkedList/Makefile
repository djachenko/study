tester.out: tester.o LinkedList.o
	g++ -o tester.out tester.o LinkedList.o

LinkedList.o: LinkedList.cpp LinkedList.h
	g++ -c -g -o LinkedList.o LinkedList.cpp

tester.o: tester.cpp LinkedList.h
	g++ -c -g -o tester.o tester.cpp
	
clean:
	rm *.out
