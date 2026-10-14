#include <stdio.h>
#include <stdlib.h>

int max(int a,int b,int x,int y)
{
	if (a>=b) return(x);

	return(y);
}

void sift (int *a,int k,int N)
{
	if (2*k+1>=N) return;

	int m;

	if (2*k+2==N) m=2*k+1;
	if (2*k+2<N) m=max(a[2*k+1],a[2*k+2],2*k+1,2*k+2);

	if (a[k]<a[m])
	{
		int b=a[k];
		a[k]=a[m];
		a[m]=b;

		sift(a,m,N);
	}
}

int main()
{
	freopen("input.txt","r",stdin);

	int N;

	scanf("%d",&N);

	int *a=malloc(N*sizeof(int));

	int i;

	for (i=0;i<N;i++)
		scanf("%d",&a[i]);

	for (i=(N-1)/2;i>=0;i--)
			sift(a,i,N);

	for(i=N-1;i>=0;i--)
	{
		sift(a,0,i+1);

		int b=a[0];
		a[0]=a[i];
		a[i]=b;
	}

	for(i=0;i<N;i++)
		printf("%d ",a[i]);

	putchar('\n');

	return(0);
}
