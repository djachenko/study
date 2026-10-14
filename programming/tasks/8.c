#include <stdio.h>
#include <math.h>

#define N 751
#define M 1000

struct dot
{
	int x;
	int y;
};

int sqr(int a)
{
	return a*a;
}

double len(struct dot a, struct dot b)
{
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

void prim()
{

}

int main()
{
	FILE *f=fopen("input.txt","r");
	freopen("output.txt","w",stdout);

	int n;

	fscanf(f,"%d",&n);

	int i;

	struct dot towns[N];

	for (i=1;i<=n;i++)
	{
		fscanf(f,"%d%d",&towns[i].x,&towns[i].y);
	}

	int j;

	double a[N][N];

	int x;
	int y;

	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
		{
			a[i][j]=len(towns[i],towns[j]);//матрица смежности
		}
	}

	int m;

	fscanf(f,"%d",&m);

	for (i=1;i<=m;i++)
	{
		fscanf(f,"%d%d",&x,&y);//заданные дороги пусть с нулевым весом

		a[x][y]=0;
		a[y][x]=0;
	}

	struct roads
	{
		int from;
		int to;
	} T[M];//дороги (нужные и построенные)

	struct distance
	{
		double length;
		int parent;
	} d[N];//расстояния от вершин до графа

	for (i=1;i<=n;i++)
	{
		d[i].length=40000;
		d[i].parent=-1;
	}

	int b[N]={0};

	int curr=1;
	int k;

	for(k=1;k<=n;k++)
	{
		double min;
		int mini;

		b[curr]=1;

		for (i=1;i<=n;i++)
		{
			if (a[curr][i]<d[i].length)
			{
				d[i].length=a[curr][i];
				d[i].parent=curr;
			}
		}

		min=40000;
		mini=0;

		for (i=1;i<=n;i++)
		{
			if (!b[i] && d[i].length<min)
			{
				min=d[i].length;
				mini=i;
			}
		}

		T[k].from=d[mini].parent;
		T[k].to=mini;
		curr=mini;
	}

	for (i=1;i<=k;i++)
	{
		if (a[T[i].from][T[i].to])
			printf("%d %d\n",T[i].from,T[i].to);
	}

	return 0;
}

