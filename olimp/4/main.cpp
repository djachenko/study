#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream output("output.txt");

    output << "NOBODY LOSES" << endl;

    return 0;
}
