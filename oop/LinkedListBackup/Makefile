tester.out: tester.o 
	g++ -o tester.out tester.o 

tester.o: tester.cpp LinkedList.h
	g++ -c -g -o tester.o tester.cpp
	
clean:
	rm *.out
