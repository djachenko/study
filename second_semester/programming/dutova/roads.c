#include <stdio.h>

int deep(int a[11][11], int b[11], int curr, int dest, int size, int Y)
{
	if (0>Y)//esli previshena dopustimaya dlina vozrachaet 0
	{
		return 0;
	}

	if (curr==dest)//dostignuta itogovaya vershina
	{
		return 1;
	}

	b[curr]=1;//were

	int i;

	int sum=0;

	for(i=1;i<=size;i++)
	{
		if (!b[i] && a[curr][i])
		{
			sum+=deep(a,b,i,dest,size,Y-1);
		}
	}

	b[curr]=0;

	return sum;
}

int main()
{
	int a[11][11]={{0}};

	int N;

	printf("size: ");

	scanf("%d",&N);//size reading

	int x;
	int y;

	printf("roads:\n");//priglashenie k vvodu

	while (1)
	{
		scanf("%d%d",&x,&y);

		if (x==0 && y==0)
		{
			break;
		}

		a[x][y]=1;
	}

	int A;
	int B;

	printf("from and to:\n");//iz kokogo goroda v kakoy
	scanf("%d%d",&A,&B);

	int Y;

	printf("Y: ");

	scanf("%d",&Y);//shitivaem dliny puti

	int b[11]={0};//0-ne bili 1-bili

	printf("%d\n",deep(a,b,A,B,N,Y));//obhod v glubinu

	return 0;
}
