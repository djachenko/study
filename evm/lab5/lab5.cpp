#include <iostream>
#include <fstream>

#include <stdlib.h>

#include "FMatrix.h"

#define size 6

int main()
{
	ifstream input;

	input.open("lab5.txt");

	FMatrix lab5(size, size);

	input >> lab5;

	input.close();

	FMatrix b = B(lab5);

	cout << lab5;

	cout << lab5.l() << ' ' << lab5.w() << endl;

	cout << b << endl;

	cout << "check1" << endl;

	b*=432;

	cout << "check2" << endl;

	cout << b;

	FMatrix antiLab(size, size);

	FMatrix r = E( lab5.height() );

	cout << "check3" << endl;

	FMatrix test = R(lab5);

	cout << "check4" << endl;

	cout << r;

	for (int i = 0; i < 10000; i++)
	{
		cout << "i: " << i << endl;

		antiLab += r;

		cout << "2" << endl;

		r = R(lab5);

		cout << "3" << endl;
	}

	antiLab *= B(lab5);

	FMatrix result (lab5);

	result = result * antiLab;


	cout << "result:" << endl;
	cout << result;

	return 0;
}
