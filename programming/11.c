#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sys(int a,int b)//vypisyvanie celoy
{
	if (a==0) return;

    	sys(a/b,b);
	
	if (a%b>9) 
	{
		printf("%c",a%b-10+'A');
		return;
	}

    	printf("%d",a%b);

    	return;
}

int main()
{
	int b;
    	double x;

    	scanf("%d%lf",&b,&x);

    	sys(x,b);
	
//	printf("was: %lf\n", x);
    	x-=(int)x;
//	printf("now: %lf\n", x);

	if (x) putchar('.');

	int deep;

	for(deep=4;x && deep;deep--)
    	{
        	x*=b;
        	printf("%.0lf",0.0+(int)x);
//		printf("was: %lf\n", x);
		x-=(int)x;  
//		printf("now: %lf\n", x);
    	}

	putchar('\n');

    	return 0;
}
