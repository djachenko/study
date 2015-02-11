#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int size;

	cin >> size;

	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << rand() % 1000 << ' '; 
		}

		cout << endl;
	}

	return 0;
}
