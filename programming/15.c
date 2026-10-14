#include <stdio.h>

int main()
{
#define x 100000

//	freopen("input.txt","rt",stdin);
//	freopen("output.txt","wt",stdout);

	int n;
	int a[x];
//	int b[x];

	scanf("%d",&n);

	int i;
	
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
//		b[i]=0;
	}

//	for(i=0;i<n;i++)
//		printf("%d ",a[i]);
//		printf("\n");
	int min;
	int index;
	
	for(i=0;i<n;i++)
	{
//		printf("(%d) ",i);

		int z;

//		for(z=0;z<n;z++)
//			printf("%d ",a[z]);
//			printf("\n");

		min=a[i];
		index=-1;

		int k;

		for(k=i;k<n;k++)
			
			if (a[k]<min) 
			{
				min=a[k];
				index=k;
			}

		for(k=index-1;k>=i;k--)
			a[k+1]=a[k];

		a[i]=min;	
	}

	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");

	return(0);		
}
