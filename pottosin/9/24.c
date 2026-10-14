#include <stdio.h>
#include <string.h>

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int map[102][102]={0};

	int N;
	int M;

	scanf("%d%d",&M,&N);
	getchar();

	int x;
	int y;

	for (x=0;x<=N+1;x++)
	{
		for (y=0;y<=M+1;y++)
		{
			map[x][y]=-1;
		}
	}

	int c;

	int startq[10000][2]={0};//massivi pod ozered
	int startn=0;

	for (x=0;x<=M+1;x++)
	{
		map[x][0]=0;
		map[x][N+1]=0;
	}
	
	for(x=1;x<=M;x++)
	{
		for(y=1;y<=N;y++)
		{
			map[0][y]=0;
			map[M+1][y]=0;

			c=getchar();

			if (c=='#')
			{
				map[x][y]=1;
				startq[startn][0]=x;
				startq[startn][1]=y;

				startn++;
			}

			if (c=='-')
			{
				map[x][y]=0;
			}
		}

		getchar();
	}

	int queue[10000][2]={0};//massiv pod ozered
	int maxway=0;
	int arts[2][2]={{0}};
	int way[102][102]={{0}};

	int i;

	for (i=0;i<startn;i++)
	{
		memset(queue,0,10000*2*sizeof(int));
		memset(way,0,102*102*sizeof(int));

		queue[0][0]=startq[i][0];
		queue[0][1]=startq[i][1];

		way[queue[0][0]][queue[0][1]]=1;

		int l=-1;//levo
		int r=0;//pravo

		int n=0;

		while (1)
		{
			l++;

			if (r<l)
			{
				break;
			}

			n++;

			x=queue[l][0];
			y=queue[l][1];

			if (map[x+1][y] && way[x+1][y]<way[x][y] && !way[x+1][y])
			{
				way[x+1][y]=way[x][y]+1;
	
				r++;
				queue[r][0]=x+1;
				queue[r][1]=y;
			}
			if (map[x][y+1] && way[x][y+1]<way[x][y] && !way[x][y+1])
			{
				way[x][y+1]=way[x][y]+1;
	
				r++;
				queue[r][0]=x;
				queue[r][1]=y+1;
			}
			if (map[x-1][y] && way[x-1][y]<way[x][y] && !way[x-1][y])
			{
				way[x-1][y]=way[x][y]+1;
	
				r++;
				queue[r][0]=x-1;
				queue[r][1]=y;
			}
			if (map[x][y-1] && way[x][y-1]<way[x][y] && !way[x][y-1])
			{
				way[x][y-1]=way[x][y]+1;
	
				r++;
				queue[r][0]=x;
				queue[r][1]=y-1;
			}
		}

		int max=-1;
		int art[2]={0};

		for (x=1;x<=M;x++)
		{
			for (y=1;y<=N;y++)
			{
				if (way[x][y]>max)
				{
					max=way[x][y];

					art[0]=x;
					art[1]=y;
				}
			}
		}

		if (max>maxway)
		{
			maxway=max;

			arts[0][0]=startq[i][0];
			arts[0][1]=startq[i][1];

			arts[1][0]=art[0];
			arts[1][1]=art[1];
		}

	}

	map[arts[0][0]][arts[0][1]]=2;
	map[arts[1][0]][arts[1][1]]=2;

	for(x=1;x<=M;x++)
	{
		for(y=1;y<=N;y++)
		{
			if (map[x][y]==0)
			{
				printf("-");	
			}
			if (map[x][y]==1)
			{
				printf("#");
			}
			if (map[x][y]==2)
			{
				printf("X");
			}
		}

		putchar('\n');
	}


	return(0);
}
