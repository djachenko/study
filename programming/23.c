#include <stdio.h>
//glubinAaZZ
int main()
{
	freopen("23.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int a[101][101];
	int b[101];
	int d[101];

	int N;
	int M;

	scanf("%d%d",&N,&M);

	int x;
	int y;

	for(x=1;x<=N;x++)
	{
		for(y=1;y<=N;y++)
			a[x][y]=0;

		d[x]=0;
		b[x]=0;
	}

	int i;

	for(i=0;i<M;i++)
	{
		scanf("%d%d",&x,&y);
		a[x][y]=1;
		a[y][x]=1;
	}

	d[0]=1;
	int k=1;

	int l=0;
	int r=0;
	x=1;
	b[1]=1;

	do
	{
		printf("%d ",x);

		for(i=1;i<=N;i++)
			if (a[x][i] && !b[i])
			{
				r++;
				d[r]=i;
				b[i]=1;
			}

		l++;
		x=d[l];
	}
	while (r>=l);

	putchar('\n');

	return(0);
}
