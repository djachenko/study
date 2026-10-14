#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
	double b;
	char s[255];

	scanf("%lf",&b);
	scanf("%s",s);

	int point;

	point=strchr(s,'.')-s;
	if (point+s==0) point=strlen(s);

	int i;
//	int l=strlen(s);

	double num=0;
	double step=pow(b,(point-1)*1.0);
//	printf("point %d\n",point);

	int l=strlen(s);

	for(i=0;i<l;i++)
	{
		if (i!=point)
		{
			step/=b;

			num+=(s[i]-'0')*step;
		}
	}

	printf("%f\n",num);

	return(0);

}
