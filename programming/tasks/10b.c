#include <stdio.h>

struct gangster
{
	int time;
	int prosperity;
	int stoutness;
};

int submax(int a,int b)
{
	if (a>b)
		return a;
	else
		return b;
}

int max(int a, int b, int c)
{
	return submax(submax(a,b),submax(a,c));
}

int select(struct gangster * a, int t, int s, int n)
{
	int i;
	int max=0;

	for (i=0;i<n;i++)
	{
		if (a[i].time==t && a[i].stoutness==s && a[i].prosperity>max)
		{
				max=a[i].prosperity;
		}
	}

	return max;
}

int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int N;
	int K;
	int T;

	scanf("%d%d%d",&N,&K,&T);

	int i;

	struct gangster gangsters[100];

	for (i=0;i<N;i++)
		scanf("%d",&gangsters[i].time);

	for (i=0;i<N;i++)
		scanf("%d",&gangsters[i].prosperity);

	for (i=0;i<N;i++)
		scanf("%d",&gangsters[i].stoutness);

	int matrix[3001][101]={{0}};

	int j;

	matrix[0][0]=select(gangsters,0,0,N);

	for (i=1;i<=K;i++)
	{
		matrix[i][0]=submax(matrix[i-1][0],matrix[i-1][1]);
		matrix[i][i+1]=0;
		matrix[i][i]=select(gangsters,i,i,N)+matrix[i-1][i-1];

		for (j=1;j<i;j++)
		{
			matrix[i][j]=select(gangsters,i,j,N)+max(matrix[i-1][j-1],matrix[i-1][j],matrix[i-1][j+1]);
		}
	}

	for (i=K+1;i<=T;i++)
	{
		matrix[i][0]=submax(matrix[i-1][0],matrix[i-1][1]);

		for (j=1;j<K;j++)
		{
			matrix[i][j]=select(gangsters,i,j,N)+max(matrix[i-1][j-1],matrix[i-1][j],matrix[i-1][j+1]);
		}

		matrix[i][K]=select(gangsters,i,K,N)+submax(matrix[i-1][K-1],matrix[i-1][K]);
	}

	for (i=0;i<=K;i++)
	{
		for (j=0;j<=T;j++)
		{
			printf("%3d",matrix[j][i]);
		}

		putchar('\n');
	}

	int max=0;

	for (i=0;i<=K;i++)
	{
		if (matrix[T][i]>max)
		{
			max=matrix[T][i];
		}
	}

	printf("%d\n",max);

	return 0;
}
