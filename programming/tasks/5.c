#include <stdio.h>
#include <math.h>

#define N 14

struct cell
{
	int x1;
	int y1;
	int x2;
	int y2;
};

int max(int a, int b)
{
	if (a>b)
		return a;

	return b;
}

int min(int a, int b)
{
	if (a<b)
		return a;

	return b;
}

int check(struct cell a, struct cell b)//проверяет, по какие стороны от a лежат вершины b
{
	a.x2-=a.x1;
	b.x1-=a.x1;
	b.x2-=a.x1;
	a.x1=0;

	a.y2-=a.y1;
	b.y1-=a.y1;
	b.y2-=a.y1;
	a.y1=0;

	int s1=a.x2*b.y1-a.y2*b.x1;
	int s2=a.x2*b.y2-a.y2*b.x2;

	if (s1==0 && s2==0)
	{
		if (a.x1==a.x2)
		{
			if (min(a.y1,a.y2)<=max(b.y1,b.y2) && min(b.y1,b.y2)<=max(a.y1,a.y2))
				return 1;
		}
		else
		{
			if (min(a.x1,a.x2)<=max(b.x1,b.x2) && min(b.x1,b.x2)<=max(a.x1,a.x2))
				return 1;
		}

		return 0;
	}

	if (s1*s2<=0)
		return 1;

	if (s1*s2>0)
		return 0;
}

int deep(int a[N][N], int b[N], int x, int y, int n)
{
	if (x==y)
		return 1;

	b[x]=1;

	int i;
	int sum=0;

	for (i=1;i<=n;i++)
	{
		if (a[x][i] && !b[i])
			sum+=deep(a,b,i,y,n);
	}

	return sum;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int n;

	while(1)
	{
		scanf("%d",&n);

		if (n==0)
		{
			return 0;
		}

		int i;
		int j;

		struct cell segments[N];

		for (i=1;i<=n;i++)
		{
			scanf("%d",&segments[i].x1);
			scanf("%d",&segments[i].y1);
			scanf("%d",&segments[i].x2);
			scanf("%d",&segments[i].y2);
		}

		int a[N][N]={0};

		for (i=1;i<=n;i++)
		{
			for (j=1;j<=n;j++)
			{
				if (j==i)
				{
					a[i][j]=1;
					continue;
				}

				a[i][j]=check(segments[i],segments[j])*check(segments[j],segments[i]);
			}
		}

		while (1)
		{
			int x;
			int y;
			scanf("%d%d",&x,&y);

			if (x==0 && y==0)
				break;

			int b[N]={0};

			if (deep(a,b,x,y,n))
				printf("CONNECTED\n");
			else
				printf("NOT CONNECTED\n");
		}
	}
}
