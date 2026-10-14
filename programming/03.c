#include <stdio.h>
#include <math.h>

float f(float x)
{
	return(x*x-2);
}

int main()
{
	float a=0;
	float b=333;
	float k=1;//вспомогательная, середина. 1 чтоб вошло в цикл
	float x;

	while(fabs(k)>0.001)
		{
			k=f((b-a)/2+a);

			if (fabs(k)<=0.001) printf("%f\n",(b-a)/2+a);
				else if (k<0) a=(a+(b-a)/2);
					else b=(b-(b-a)/2);
//			printf("%f %f %f\n",a,b,k);
		}

	return 0;}
