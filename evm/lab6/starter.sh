#!/bin/sh

SIZE=1024;

rm direct.txt;
for ((i=1; i<=SIZE; i++)) 
	do 
	./lab6 d $i >> direct.txt;
	done;
./converter direct.txt > direct2.txt;

rm reverse.txt;
for ((i=1; i<=SIZE; i++)) 
	do
	./lab6 b $i >> reverse.txt;
	done;
./converter reverse.txt > reverse2.txt;

rm random.txt;
for ((i=1; i<=SIZE; i++)) 
	do 
	./lab6 r $i >> random.txt;
	done;
./converter random.txt > random2.txt;

exit 0;
