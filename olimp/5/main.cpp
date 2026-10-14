#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int max(int a, int b)
{
    if ( a > b )
    {
        return a;
    }

    return b;
}

int min(int a, int b)
{
    if ( a < b )
    {
        return a;
    }

    return b;
}

struct Cell
{
    int x;
    int y;
    Cell * next;
};

#define HASHSIZE 4000

struct Square
{
    int top;
    int down;
    int left;
    int right;

    Cell * head[HASHSIZE];
    Cell * tail[HASHSIZE];
    int count;
};

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int N;

    input >> N;

    int x1;
    int y1;
    int x2;
    int y2;

    Square arr[100];

    for (int i = 0; i < N; i++)
    {
        input >> x1 >> y1 >> x2 >> y2;

        arr[i].top = max(y1, y2);
        arr[i].down = min(y1, y2);
        arr[i].left = min(x1, x2);
        arr[i].right = max(x1, x2);

        arr[i].count = 0;

        for (int j = 0; j < i; j++)
        {
            for (int x = max(arr[i].left, arr[j].left); x < min(arr[i].right, arr[j].right); x++)
            {
                for (int y = max(arr[i].down, arr[j].down); y < min(arr[i].top, arr[j].top); y++)
                {
                    bool found = false;

                    struct Cell * p = NULL;
                    int k = (x + y) % HASHSIZE;

                    for (p = arr[i].head[k]; p; p = p->next)
                    {
                        if (x == p->x && y == p->y)
                        {
                            found = true;

                            break;
                        }
                    }

                    if (!found)
                    {
                        p = new Cell;

                        p->x = x;
                        p->y = y;
                        p->next = NULL;

                        if (NULL == arr[i].head[k])
                        {
                            arr[i].head[k] = p;
                        }
                        else
                        {
                            arr[i].tail[k]->next = p;
                        }

                        arr[i].tail[k] = p;

                        arr[i].count++;
                    }
                }
            }
        }

        output << (arr[i].right - arr[i].left) * (arr[i].top - arr[i].down) - arr[i].count << endl;
    }

    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < HASHSIZE; k++)
        {
            struct Cell * p = arr[i].head[k];
            struct Cell * q = NULL;

            for ( ; ; )
            {
                if (NULL == p)
                {
                    break;
                }

                q = p->next;

                delete p;

                p = q;
            }
        }
    }

    return 0;
}
