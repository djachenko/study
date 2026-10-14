#!/bin/bash

for k in 0 1 2 3
do
	gcc -O$k -o 2.out 2.c;
	
	echo "gcc -O$k -o 2.out 2.c";

	for j in 0 1 2 3 4 5 6 7 8 9
	do
		sync;
		cat input | ./2.out;
	done

	echo;
	
	gcc -O$k -o 2.out 2.c;
	
	echo "gcc -O$k -mtune=native -o 2.out 2.c";

	for j in 0 1 2 3 4 5 6 7 8 9
	do
		sync;
		cat input | ./2.out;
	done

done

exit 0;
