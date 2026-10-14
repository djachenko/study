#include <stdio.h>

void qsort(int *a,int l,int r)
{
	if (l>=r) return;
	else
	{
		int m;
	
		m=(a[r]+a[l])/2;

		int i=l;
		int j=r;

		while (i<=j)
		{

			while (a[i]<m) i++;
			while (a[j]>m) j--;
			if (i<=j) 
			{
				int g=a[i];
				a[i]=a[j];
				a[j]=g;
				i++;
				j--;
			}
		}

		qsort(a,l,j);
		qsort(a,i,r);
	}	


}

int main()
{
#define x 100000

	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	int n;

	scanf("%d",&n);

	int i;
	int a[x];
	
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);

	qsort(a,0,n-1);

	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
		

	return(0);
}
