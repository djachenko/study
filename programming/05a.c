#include <stdio.h>

int isprime(int a)
{
	int i;

	for(i=2;i*i<=a;i++)
		if (a%i==0) return 0;

	return 1;
}

int main()
{
#define N 100000

	int M[N];
	int n;

	scanf("%d",&n);

	int i;

	for(i=0;i<n;i++)
		scanf("%d",&M[i]);

	for(i=0;i<n;i++)
		if (isprime(M[i])==0)
		 {
			 printf("0\n");
			 return (0);
		 }

	printf("1\n");
	return(0);
}
