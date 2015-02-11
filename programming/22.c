#include <stdio.h>

void deep(int a[][100],int b[],int k,int d,int N)
{
	printf("%d ", k);
	b[k]=d;

	int i;

	for(i=1;i<=N;i++)
	{
		if (!b[i] && a[k][i]) deep(a,b,i,d,N);
	}
}

int main()
{
	int a[100][100];
	int b[100];

	FILE *f=fopen("22.txt","r");
	//freopen("output.txt","w",stdout);

	int N;
	int M;

	fscanf(f,"%d %d",&N,&M);

	int x;
	int y;

	for(x=1;x<=N;x++)
	{
		for(y=1;y<=N;y++)
		{
		    a[x][y]=0;
		}
		b[x]=0;
	}

    int i;

    for(i=1;i<=M;i++)
	{
	    fscanf(f,"%d%d",&x,&y);
		a[x][y]=1;
		a[y][x]=1;
	}


    int d=0;

    for(i=1;i<=N;i++)
	{
	    if (!b[i])
	    {
	        d++;
	        deep(a,b,i,d,N);
	    }

	}
    printf("\n");

    printf("%d\n",d);

	for(i=1;i<=N;i++)
	printf("%d ",b[i]);

	fclose(f);

	return(0);
}
