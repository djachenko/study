#include <stdio.h>

void dejxtra(int k,int a[][101],int *b, int *d,int N)
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

void route(int k,int a[][101],int d[],int N)
{
	if (k==1) 
	{
		printf("1 ");
		return;
	}

	int i;

	for (i=1;i<N;i++)
	{
		if (d[k]==d[i]+a[i][k] && i!=k) 
		{
			route(i,a,d,N);
			break;
		}
	}
	
	printf("%d ",k);
	
	return;
}

int main()
{
    	freopen("24.txt","r",stdin);
    	//freopen("output.txt","w",stdout);

    	int N;
    	int M;

    	scanf("%d%d",&N,&M);

    	int i;
    	int a[101][101];
    	int b[101];//byli ili net
    	int d[101];//distances
	int p[100];
    	int x,y;

    	for(x=1;x<=N;x++)//initilization
    	{
       		for(y=1;y<=N;y++)
            		a[x][y]=-1;
        	a[x][x]=0;

        	b[x]=0;
        	d[x]=-1;
    	}

    	d[1]=0;
/*
    	for (i=0;i<M;i++)//reading matrix
    	{
        	scanf("%d%d",&x,&y);
        	scanf("%d",&a[x][y]);
        	a[y][x]=a[x][y];
    	}
*/
    	while(scanf("%d%d",&x,&y)==2)
    	{
        	scanf("%d",&a[x][y]);
        	a[y][x]=a[x][y];
    	}


    	dejxtra(1,a,b,d,N);

     	for (i=1;i<=N;i++)
        	printf("%d ",d[i]);

	printf("\n\n");

	printf("ways:\n");

	for (i=1;i<=N;i++)
	{
		printf("%d: ",i);
		route(i,a,d,N);
		putchar('\n');
	}


    	return 0;
}
