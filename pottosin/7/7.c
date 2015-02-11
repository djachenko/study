#include <stdio.h>
#include <math.h>

int quarter(double l, double w, double x, double y, double r)
{
	if (x>l)
	{
		if (y>w)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	
	if (x<0)
	{
		if (y<0)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}

	return 5;
}

double sqr(double x)
{
	return x*x;
}

double len(double x1, double y1, double x2, double y2)
{
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

int main()
{
	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);

	int N;

	scanf("%d",&N);

	double l;
	double w;
	double x;
	double y;
	double r;

	for (;N;N--)
	{
		scanf("%lf%lf%lf%lf%lf",&l,&w,&x,&y,&r);

		printf("q %d\n",quarter(l,w,x,y));

		if (x-r>l || y-r>w || x+r<0 || y+r<0)
		{
			printf("Out\n");
		}
		else
		{
			switch (quarter(l,w,x,y))
			{
				case 1:
					if (len(l,w,x,y)>r)
					{
						printf("Out\n");
					}
					else
					{
						printf("In\n");
					}

					break;
				case 2:
					if (len(l,0,x,y)>r)
					{
						printf("Out\n");
					}
					else
					{
						printf("In\n");
					}

					break;
				case 3:
					if (len(0,0,x,y)>r)
					{
						printf("Out\n");
					}
					else
					{
						printf("In\n");
					}

					break;
				case 4:
					if (len(0,w,x,y)>r)
					{
						printf("Out\n");
					}
					else
					{
						printf("In\n");
					}

					break;
				case 5:
					printf("In\n");
			}
			
		}
	}

	return 0;
}
