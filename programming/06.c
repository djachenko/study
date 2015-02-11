#include <stdio.h>

int main()
{
	#define N 1000000

	int m[N];
	int n;
	int x;
	int i;

	int b=0;

	scanf("%d",&n);
	
	int e=n-1;

	for(i=0;i<n;i++)
		scanf("%d",&m[i]);

	scanf("%d",&x);


	do
	{
		i=(e-b)/2+b;
	
		if (m[i]==x)
		{
			printf("yes\n");
			return(0);
		}
		else 
			if (m[i]<x) b=i+1;
			else e=i-1;		
	}
	while(e>=b);

	printf("no\n");

	return(0);
}
