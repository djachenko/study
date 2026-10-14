#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

#define N 20
#define M 30

int compare(const void * a, const void * b)
{
	if ((*(double*)a - *(double*)b) > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

double sqr(double a)
{
	return a*a;
}

int main()
{
	ifstream first("1.txt");
	ifstream second("2.txt");

	double X[N] = {0};
	double Y[M] = {0};

	double X_ = 0;
	double Y_ = 0;

	for (int i = 0; i < N; i++)
	{
		first >> X[i];

		X_ += X[i];
	}

	for (int i = 0; i < M; i++)
	{
		second >> Y[i];

		Y_+= Y[i];
	}

	X_ /= N;
	Y_ /= M;

	double Sx = 0;
	double Sy = 0;

	for (int i = 0; i < N; i++)
	{
		Sx += sqr(X[i] - X_) / N;
	}

	for (int i = 0; i < M; i++)
	{
		Sy += sqr(Y[i] - Y_) / M;
	}

	cout << Sx << endl << Sy << endl;

	double n = N * (M - 1) * Sx / (M * (N - 1) * Sy);

	cout << n << endl;

	cout << ((X_ - Y_) * sqrt(N + M - 2)) / (sqrt(1.0 / N + 1.0 / M) * sqrt(N * Sx + M * Sy)) << endl;

	return 0;
}
