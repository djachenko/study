#include <stdio.h>
#include <stdlib.h>

void dejxtra(int k,int a[101][101],int *b, int *d,int N)
{
    	int i;

    	for (i=1;i<=N;i++)
        	if ((a[k][i]!=-1) && (d[i]>d[k]+a[k][i] || d[i]==-1))//est rebro i (put koroche ili ne hodili)
            		d[i]=d[k]+a[k][i];

    	b[k]=1;//byli

    	int min=-1;
    	int mini;

    	for (i=1;i<=N;i++)
    	{
        	if (b[i]==0 && d[i]!=-1 && (d[i]<min || min==-1))
        	{
            		min=d[i];
            		mini=i;
        	}
    	}

    	if (min!=-1) dejxtra(mini,a,b,d,N);
    	else return;
}

void deep(int a[101][101],int b[101],int k,int N)
{
	b[k]=1;

	int i;

	for(i=1;i<=N;i++)
	{
		if (!b[i] && a[k][i]!=-1)
		{
			deep(a,b,i,N);
		}
	}
}

int main()
{
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);

	int N;
	scanf("%d",&N);

	int S1;
	int S2;
	
	scanf("%d%d",&S1,&S2);

	int a[101][101];
   	int b[101];//byli ili net
   	int d[101];//distances
   	int x,y;

   	for(x=1;x<=N;x++)//initilization
   	{
   		for(y=1;y<=N;y++)
       		a[x][y]=-1;

       	b[x]=0;
       	d[x]=-1;
   	}

	while(scanf("%d%d",&x,&y)==2)
	{
		scanf("%d",&a[x][y]);
		a[y][x]=a[x][y];
	}

	deep(a,b,S1,N);

	if (!b[S2])
	{
		printf("no\n");
		return 0;
	}

	for (x=1;x<=N;x++)
		b[x]=0;

	d[S1]=0;

	dejxtra(S1,a,b,d,N);

	printf("%d\n",d[S2]);

	return 0;
}
