#include <stdio.h>

void print_way(int a[102][102], int x, int y, int n)
{
	if (a[x][y]==1)
	{
		printf("%d %d\n",x,y);

		return;
	}

	if (a[x+1][y]==n-1)
	{
		print_way(a,x+1,y,n-1);

		printf("%d %d\n",x,y);

		return;
	}
	if (a[x][y-1]==n-1)
	{
		print_way(a,x,y-1,n-1);

		printf("%d %d\n",x,y);

		return;
	}
	if (a[x-1][y]==n-1)
	{
		print_way(a,x-1,y,n-1);

		printf("%d %d\n",x,y);

		return;
	}
	if (a[x][y+1]==n-1)
	{
		print_way(a,x,y+1,n-1);

		printf("%d %d\n",x,y);

		return;
	}
}

int main()
{
	FILE * f=fopen("24.txt","r");//otkritie faila

	int a[102][102]={0};//massiv pod labirint

	int N;//shirina
	int M;//visota

	fscanf(f,"%d%d",&N,&M);//vvodim shirinu i visotu
	fgetc(f);

	int x;//peremennie pod koordinati
	int y;//

	for (x=0;x<=N+1;x++)
	{
		for (y=0;y<=M+1;y++)
		{
			a[x][y]=-1;//zanulenie massiva ves zapolniaetsia pregradami
		}
	}

	int c;//perem

	for(x=0;x<=M+1;x++)
	{
		for(y=0;y<=N+1;y++)
		{
			c=fgetc(f);

			if (c=='#')//pregrada
			{
				a[x][y]=-1;
			}

			if (c==' ')//pustoe mesto
			{
				a[x][y]=0;
			}
		}

		fgetc(f);
	}

	putchar(' ');

	for (y=0;y<=N+1;y++)
	{
		printf("%d",y);
	}

	putchar('\n');

	for(x=0;x<=M+1;x++)
	{
		printf("%d",x);

		for(y=0;y<=N+1;y++)
		{
			if (a[x][y]==-1)
			{
				putchar('#');
			}
			else
			{
				putchar(' ');
			}
		}

		putchar('\n');
	}

	printf("rook: ");//vvesti koord ladii

	int queue[10000][2]={0};//massiv pod ozered

	scanf("%d%d",&queue[0][0],&queue[0][1]);

	printf("destination: ");

	int destx;
	int desty;

	scanf("%d%d",&destx,&desty);

	if (destx==queue[0][0] && desty==queue[0][1])//esli itogovaya tochka sovpadaet s koord ladii,to vozvrahaet noli
	{
		printf("no sense to go anywhere. relax, ma-a-n...\n");

		return 0;
	}
	
	a[queue[0][0]][queue[0][1]]=1;

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

		if (x==destx && y==desty)
		{
			break;
		}

		if (a[x+1][y]>a[x][y])
		{
			a[x+1][y]=a[x][y]+1;

			r++;
			queue[r][0]=x+1;
			queue[r][1]=y;
		}
		if (a[x][y-1]>a[x][y])
		{
			a[x][y-1]=a[x][y]+1;

			r++;
			queue[r][0]=x;
			queue[r][1]=y-1;
		}
		if (a[x-1][y]>a[x][y])
		{
			a[x-1][y]=a[x][y]+1;

			r++;
			queue[r][0]=x-1;
			queue[r][1]=y;
		}
		if (a[x][y+1]>a[x][y])
		{
			a[x][y+1]=a[x][y]+1;

			r++;
			queue[r][0]=x;
			queue[r][1]=y+1;
		}

	}

	for (y=0;y<=N+1;y++)
	{
		printf("%d",y);
	}

	putchar('\n');

	for(x=0;x<=M+1;x++)
	{
		printf("%d",x);

		for(y=0;y<=N+1;y++)
		{
			if (a[x][y]==-1)
			{
				printf("%3d",a[x][y]);	
			}
			else
			{
				printf("%3d",a[x][y]);	
			}
		}

		putchar('\n');
	}

	if (a[destx][desty]==0)
	{
		printf("sorry, no way\n");
	}
	else
	{
		print_way(a,destx,desty,a[destx][desty]);
	}

	return(0);
}
