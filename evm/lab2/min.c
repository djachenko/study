#include <stdio.h>

int main()
{
	double i;
	double min=500000;
	double a;


	for (i=0;i<10;i++)
	{
		scanf("%lf",&a);

		if (a<min)
		{
			min=a;
		}
	}

	printf("min=%lf\n",min);

	return 0;
}
