#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream input(argv[1]);

	double time = 0;
	double change = 0;

	double single = 0;

	input >> single;
	
	for (int i = 2; i <= 48; i++)
	{
		time = 0;

		for (int j = 0; j < i; j++)
		{
			double temp;

			input >> temp;

			time += temp;
		}

		time /= i;

		cout << i << ": " << time << " (" << single / time << ')' << endl;
	}

	return 0;
}
