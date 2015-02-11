#include <stdio.h>
#include <stdlib.h>

#define N 30
#define A 'A'
#define Z 'Z'

struct frame
{
	int top;
	int bottom;
	int left;
	int right;
	int flag;
	int queue[27];
	int n;
};

void enqueue(int c, struct frame *b)
{
	if (!b->queue[c-A])
	{
		b->n++;
		b->queue[c-A]=1;
	}
}

void addqueue(struct frame b[26], int k)
{
	if (!b[k].n)
		return;

	int i;

	for (i=0;i<26;i++)
	{
		if (b[k].queue[i])
		{
			addqueue(b,i);//спуститься на уровень

			int j;

			for (j=0;j<26;j++)
			{
				if (b[i].queue[j] && !b[k].queue[j])//если есть транзитивная рамка
				{
					b[k].queue[j]=1;//добавить
					b[k].n++;//увеличить количество
				}
			}
		}
	}
}

void print(struct frame b[26], int m[26], int l[26], int k, int num)
{
	int i;

	if (k==num)
	{
		for (i=0;i<k;i++)
		{
			printf("%c",l[i]+A);
		}
		putchar('\n');

		return;
	}

	for(i=0;i<26;i++)
	{
		if (!m[i] && b[i].flag && b[i].n==0)//если: не посетили (не дописали), вершина была и она на нулевом уровне
		{
			l[k]=i;//дописали
			m[i]=1;//пометка, что были

			int j;

			for (j=0;j<26;j++)//вынос ее из всей таблицы
			{
				if (b[j].queue[i])
				{
					b[j].n--;
				}
			}

			print(b,m,l,k+1,num);

			for (j=0;j<26;j++)//вынос ее из всей таблицы
			{
				if (b[j].queue[i])
				{
					b[j].n++;
				}
			}

			m[i]=0;
		}
	}
}

int main()
{
	FILE *f=fopen("input.txt","r");
	freopen("output.txt","w",stdout);

	int h;
	int w;

	while (fscanf(f,"%d%d",&h,&w)==2)
	{
		int i;
		int j;

		int a[N][N]={0};
		struct frame b[26];

		for (i=0;i<26;i++)
		{
			b[i].top=30;
			b[i].right=-1;
			b[i].left=30;
			b[i].bottom=-1;
			b[i].flag=0;
			b[i].n=0;

			for (j=0;j<26;j++)
			{
				b[i].queue[j]=0;
			}
		}

		int c=fgetc(f);

		for (i=0;i<h;i++)
		{
			for (j=0;j<w;j++)
			{
				c=fgetc(f);

				if (c=='\n')
					c=fgetc(f);

				a[i][j]=c;

				if (c>=A && c<=Z)
				{
					if (i>b[c-A].bottom)
						b[c-A].bottom=i;
					if (i<b[c-A].top)
						b[c-A].top=i;
					if (j>b[c-A].right)
						b[c-A].right=j;
					if (j<b[c-A].left)
						b[c-A].left=j;

					b[c-A].flag=1;
				}
			}
		}

		int num=0;

		for (i=0;i<26;i++)
		{
			if (b[i].flag==0)
				continue;

			num++;

			for (j=b[i].top;j<=b[i].bottom;j++)
			{
				if (a[j][b[i].left]!=(A+i))
					enqueue(i+A,b+a[j][b[i].left]-A);//символ, номер ячейки
				if (a[j][b[i].right]!=(A+i))
					enqueue(i+A,b+a[j][b[i].right]-A);
			}

			for (j=b[i].left;j<=b[i].right;j++)
			{
				if (a[b[i].top][j]!=(A+i))
					enqueue(i+A,b+a[b[i].top][j]-A);
				if (a[b[i].bottom][j]!=(A+i))
					enqueue(i+A,b+a[b[i].bottom][j]-A);
			}
		}

		for (i=0;i<26;i++)
			addqueue(b,i);

		int l[26]={0};
		int m[26]={0};

		print(b,m,l,0,num);
	}
	return 0;
}
