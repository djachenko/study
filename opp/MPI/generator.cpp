#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main()
{
	int size = 2;

	cin >> size;

	srand(time(NULL));

	ifstream matrixInput("matrix.txt");
	ifstream vectorInput("f.txt");

	ofstream matrixOutput("matrix.bin", ios::binary);
	ofstream vectorOutput("f.bin", ios::binary);
	ofstream sizeOutput("sizes.txt");

	sizeOutput << size << ' ' << size;
			
	float x;// =rand() % 10000 / 100.0; 

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i==j)
			{
				x = 2;
			}
			else
			{
				x = 1;
			}

			matrixOutput.write((char*)&x, sizeof(x));
		}

		x = size + 1;

		vectorOutput.write((char*)&x, sizeof(x));
	}

	matrixOutput.close();
	vectorOutput.close();

	return 0;
}
