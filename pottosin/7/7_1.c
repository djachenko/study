#include <stdio.h>
#include <math.h>

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
	freopen("output.txt","w",stdout);

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
		if (x<0)
		{
			if (y<0)
			{
				if (len(x,y,0,0)>r)
				{
					printf("Out\n");
				}
				else
				{
					printf("In\n");
				}

				continue;
			}

			if (y>w)
			{
				if (len(x,y,0,w)>r)
				{
					printf("Out\n");
				}
				else
				{
					printf("In\n");
				}

				continue;
			}

			if (x+r<0)
			{
				printf("Out\n");
			}
			else
			{
				printf("In\n");
			}

			continue;
		}
		
		if (x>l)
		{
			if (y<0)
			{
				if (len(x,y,l,0)>r)
				{
					printf("Out\n");
				}
				else
				{
					printf("In\n");
				}

				continue;
			}

			if (y>w)
			{
				if (len(x,y,l,w)>r)
				{
					printf("Out\n");
				}
				else
				{
					printf("In\n");
				}

				continue;
			}
			
			if (x-r>l)
			{
				printf("Out\n");
			}
			else
			{
				printf("In\n");
			}

			continue;
		}

		if (y-r>w)
		{
			printf("Out\n");
			
			continue;
		}

		if (y+r<0)
		{
			printf("Out\n");
			
			continue;
		}

		printf("In\n");}

	return 0;
}
