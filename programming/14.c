#include <stdio.h>

void permutation(int k, int n, int m[][2],int l[])
{
	int i;

//	printf("(%d) ",k);
//	for(i=0;i<n;i++)
//		printf("%d ",l[i]);
//		printf("\n");

	

	if (k==1)
	{
		i=0;
		while (m[i][2]==0)
			i++;
		l[n-1]=m[i][1];

		for (i=0;i<n;i++)
			printf("%d ",l[i]);
		
		l[n-1]=0;
		printf("\n");
		return;
	}
	else
		for(i=0;i<n;i++)
		{
			if (m[i][2]==1)
			{
				m[i][2]=0;
				l[n-k]=m[i][1];
				permutation(k-1,n,m,l);
				l[n-k]=0;
				m[i][2]=1;
			}
		}
}

int main()
{
#define x 100

	int n;

	scanf("%d",&n);

	int M[x][2];
	int L[x];
	int i;

	for(i=0;i<n;i++)
	{
		M[i][1]=i+1;
		M[i][2]=1;
		L[i]=0;
//		printf("%d %d\n",M[i][1],M[i][2]);
	}

	permutation(n,n,M,L);
		

	return(0);
}
