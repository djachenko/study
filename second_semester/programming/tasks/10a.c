#include <stdio.h>
#include <math.h>

int main()
{
	freopen("10a.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int N;
	int K;

	scanf("%d%d",&N,&K);

	int i;

	int nums[10000];

	for (i=0;i<N;i++)
	{
		scanf("%d",&nums[i]);
	}

	int matrix[10000][100]={{0}};

	matrix[0][abs(nums[0])%K]=1;

	int j;

	for (i=1;i<N;i++)
	{
		for (j=0;j<K;j++)
		{
			if (matrix[i-1][j])
			{
				matrix[i][abs((j+nums[i]))%K]=1;
				matrix[i][abs((j-nums[i]))%K]=1;
			}
		}
	}

	if (matrix[N-1][0])
		printf("Divisible\n");
	else
		printf("Not divisible\n");

	return 0;
}
