#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

long double sqr(long double x)
{
    return x * x;
}

long double min(long double a, long double b)
{
    if (a < b)
    {
        return a;
    }

    return b;
}

long double max(long double a, long double b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

double pi = 3.14159265;

struct cell
{
    int x;
    int y;
    struct cell * next;
}

int main()
{
    ifstream input("input.txt");
    FILE * output = fopen("output.txt", "w");

    long double x1;
    long double y1;
    long double r1;

    input >> x1 >> y1 >> r1;

    long double x2;
    long double y2;
    long double r2;

    input >> x2 >> y2 >> r2;

    long double l = sqrt(sqr(x1 - x2) + sqr(y1 - y2));

    long double p = 0.5 * (r1 + r2 + l);

    long double s = sqrt(p * (p - l) * (p - r1) * (p - r2));

    long double h = 2 * s / l;

    long double alpha = asin(h / r1);
    long double beta = asin(h / r2);
    double res = 2 * (alpha * r1 + beta * r2);

    if (l > max(r1, r2))
    {
        fprintf(output, "%lllf\n", res);
    }
    else
    {
        fprintf(output, "%lllf\n", 2 * pi * min(r1, r2) - res);
    }

    fclose(output);

    return 0;
}
