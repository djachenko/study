#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void arr_copy(double *dst,const double * src)
{
	int i;

	for(i=0;src[i];i++)
	dst[i]=src[i];

	return;
}

double sqr(double x)
{
	return(x*x);
}

double len(double x1, double y1, double x2, double y2)
{
	return(sqrt(sqr(x1-x2)+sqr(y1-y2)));
}

void deep(double (*a)[101],int *b,double *max_way,double *cur_way,int k,int N,int depth)
{
	if (k==1 && b[1])//если в начале, причем уже были (первый заход)
	{
		if(depth==N+1)//если пробежали все...
		{
			if (cur_way[0]<max_way[0] || max_way[0]==0) arr_copy(max_way,cur_way);//... и путь оказался короче
			return;
		}

		return;
	}

	int i;

	for(i=1;i<=N;i++)
	{
		if ((!b[i] || i==1) && a[k][i]) //если не были или 1 - вернуться в начало-то надо
		{
			cur_way[depth]=i;//добавляем в стек
			cur_way[0]+=a[k][i];//прибавляем длину предстоящего пути

			b[k]=1;//Для этого захода считаем, что были

			deep(a,b,max_way,cur_way,i,N,depth+1);

			cur_way[depth]=0;
			cur_way[0]-=a[k][i];

			b[k]=0;//а для следующих не были
		}
	}

	return;
}


int main()
{
	freopen("25.txt","r",stdin);

	int N;//num of nodes

	scanf("%d",&N);

	int i;
	int x,y;

	double a[101][101];//matrix
	/*
	в матрице хранятся не вершины, а расстояния
	вершины считаются с 1
	*/

	int b[101];//флаги

	double max_way[101];
	double cur_way[101];
	//в путях нулевой эл-т - сумма пути

	for (x=0;x<=N;x++)//зануление всего, что только можно
	{
		for (y=0;y<=N;y++)
			a[x][y]=0;

		b[x]=0;
		max_way[x]=0;
		cur_way[x]=0;
	}

	double arr_x[101];//массивы точек
	double arr_y[101];

	for (i=1;i<=N;i++)
	{
		scanf("%lf%lf",&arr_x[i],&arr_y[i]);//читаем точки
	}

	for (x=1;x<=N;x++)
		for(y=1;y<=N;y++)
			a[x][y]=len(arr_x[x],arr_y[x],arr_x[y],arr_y[y]);//забиваем в матрицу РАССТОЯНИЯ

	//точки далее не важны, они остаются только как номера вершин

	deep(a,b,max_way,cur_way,1,N,1);

	for(i=1;i<=N;i++)
	printf("%.0lf ",max_way[i]);

	putchar('\n');

	return(0);
}
