#include <iostream>

using namespace std;

#define N 60
#define M (N / 4)
#define GC 10
#define R (1)

int main()
{
	double * u = new double[N];
	double * uc = new double[N];

	for (int i = 0; i < M; i++)
	{
		uc[i] = 1;
	}

	for (int i = M; i < N; i++)
	{
		uc[i] = 0;
	}

	for (int generation = 0; generation < GC; generation++)
	{
		for (int i = 1; i < N; i++)
		{
			u[i] = uc[i] - R * (uc[i] - uc[i - 1]);
		}

		for (int i = 0; i < N; i++)
		{
			cout << u[i] << ' ';
		}

		cout << endl;

		double * temp = uc;
		uc = u;
		u = temp;
	}

	delete[] uc;
	delete[] u;

	return 0;
}
