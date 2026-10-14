#include <stdio.h>

int main(int argc, char ** argv)
{
	freopen(argv[1],"r",stdin);

	int a[20]={0};
	double b[20]={0};
	
	for(int i=0; i<20; i++) 
	{
		scanf("%d%lf", &a[i], &b[i]);
	}

	for (int i=0; i<20; i++)
	{
		printf("%d	", a[i]);
	}

	putchar('\n');

	for (int i=0; i<20; i++)
	{
		printf("%lf	", b[i]);
	}

	return 0;
}
