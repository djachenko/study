#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

double sqr(double a)
{
    return a * a;
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int N = 0;

    input >> N;

    int x;
    int y;

    int i;
    int j;

    for ( ; N--; )
    {
        input >> x >> y;

        if (x == 0 && y == 0)
        {
            output << "1" << endl;

            continue;
        }

        int num = max(abs(x), abs(y));
        int size = num * 2 + 1;

        int left = -num;
        int right = num;
        int top = num;
        int down = -num;

        int res = sqr(size - 2);

        if (x == right && y != down)
        {
            res += abs(y - down);

            output << res << endl;

            continue;
        }
        else
        {
            res += size - 1;
        }

        if (y == top && x != right)
        {
            res += abs(right - x);

            output << res << endl;

            continue;
        }
        else
        {
            res += size -1;
        }

        if (x == left && y!= top)
        {
            res += abs(top - y);

            output << res << endl;

            continue;
        }
        else
        {
            res += size - 1;
        }

        if (y == down && x != left)
        {
            res += abs(x - left);

            output << res << endl;

            continue;
        }
    }

    return 0;
}
