#include <stdio.h>
#include <math.h>

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

void qsort(struct gangster *a,int l,int r)
{
	if (l>=r) return;
	else
	{
		int m;

		m=(a[r].time+a[l].time)/2;

		int i=l;
		int j=r;

		while (i<=j)
		{

			while (a[i].time<m) i++;
			while (a[j].time>m) j--;
			if (i<=j)
			{
				struct gangster g;

				g.time=a[i].time;
				g.prosperity=a[i].prosperity;
				g.stoutness=a[i].stoutness;

				a[i].time=a[j].time;
				a[i].prosperity=a[j].prosperity;
				a[i].stoutness=a[j].stoutness;

				a[j].time=g.time;
				a[j].prosperity=g.prosperity;
				a[j].stoutness=g.stoutness;

				i++;
				j--;
			}
		}

		qsort(a,l,j);
		qsort(a,i,r);
	}
}


int main()
{
	int N;
	int K;
	int T;

	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	scanf("%d%d%d",&N,&K,&T);

	struct gangster gangsters[101]={0};

	int i;

	for (i=0;i<N;i++)//чтение
	{
		scanf("%d",&gangsters[i].time);
	}
	for (i=0;i<N;i++)
	{
		scanf("%d",&gangsters[i].prosperity);
	}
	for (i=0;i<N;i++)
	{
		scanf("%d",&gangsters[i].stoutness);
	}

	qsort(gangsters,0,N-1);//расположение гангстеров в порядке прихода.

	for (i=0;i<N;i++)
	{
		if (gangsters[i].stoutness>gangsters[i].time)
			gangsters[i].prosperity=0;
	}

	int j;

	for (i=1;i<N;i++)
	{
		int max=0;

		for (j=i-1;j>=0;j--)
		{
			if (gangsters[j].prosperity>max && abs(gangsters[i].time-gangsters[j].time)>=abs(gangsters[i].stoutness-gangsters[j].stoutness))
				max=gangsters[j].prosperity;
		}

		gangsters[i].prosperity+=max;
	}

	int max=0;

	for (i=0;i<N;i++)
	{
		if (gangsters[i].prosperity>max)
			max=gangsters[i].prosperity;
	}

	printf("%d\n",max);

	return 0;
}
