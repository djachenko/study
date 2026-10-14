#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	int size;

	cin >> size;

	srand(time(NULL));

	ofstream matrixOutput("matrix.bin", ios::binary);
	ofstream vectorOutput("vector.bin", ios::binary);
	ofstream sizeOutput("sizes.txt");

	sizeOutput << size << ' ' << size;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			float x =rand() % 10000 / 100.0; 

			cout << setw(5) << x << ' ';

			matrixOutput.write((char*)&x, sizeof(x));
		}

		float y = i+1;// rand() % 10000 / 100.0;

		cout << endl;

		vectorOutput.write((char*)&y, sizeof(y));
	}

	matrixOutput.close();
	vectorOutput.close();

	return 0;
}
