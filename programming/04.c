#include <stdio.h>
/*
int period(int t,int *m)
{
    int i;
    int time;

    for(i=1;i<t;i++);
	{
		time+=m[i];
		if ((g1%4==0 && g1%100!=0) || (g1%400==0) && (i==2)) t1++;
	}
}
*/
int main()
{
	int M[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

	int d1;
	int m1;
	int g1;
	long int t1;

	int d2;
	int m2;
	int g2;
	long int t2;

	int i;

	scanf("%d%d%d%d%d%d", &d1, &m1, &g1, &d2, &m2, &g2);

	t1=d1;

	for(i=1;i<m1;i++)
	{
		t1+=M[i];
		if (((g1%4==0 && g1%100!=0) || (g1%400==0)) && (i==2)) t1++;
	}

	for(i=1;i<g1;i++)
	{
		if ((i%4==0 && i%100!=0) || (i%400==0)) t1+=366;
		else t1+=365;
    	}

	t2=d2;

	for(i=1;i<m2;i++)
	{
		t2+=M[i];
		if ((g2%4==0 && g2%100!=0) ||  (g2%400==0) && (i==2)) t2++;
	}

	for(i=1;i<g2;i++)
	{
		if ((i%4==0 && i%100!=0) || (i%400==0)) t2+=366;
		else t2+=365;
	}

	printf("%d\n",abs(t2-t1));

	return 0;
}
