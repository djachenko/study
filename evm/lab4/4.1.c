#include <stdio.h>

#define N 50000 

int main()
{
	int a[N]={0};

	int i;
	int j;

	for (i=0;i<N;i++)
	{
		scanf("%d",&a[i]);
	}

	for (i=0;i<N;i++)
	{
		for (j=1;j<N;j++)
		{
			if (a[j]<a[j-1])
			{
				int b=a[j];
				a[j]=a[j-1];
				a[j-1]=b;
			}
		}
	}

	for (i=0;i<N;i++)
	{
		printf("%d",&a[i]);
	}

	return 0;
}
