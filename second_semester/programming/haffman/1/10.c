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
	int l=strlen(s);

	for(i=0;i<l;i++)
	{
		s[i]=tolower(s[i]);

        if (s[i]>='a' && s[i]<='z')
	    	s[i]=s[i]-('a'-'0'-10);

		if (s[i]!='.')
            s[i]-='0';
	}


	double num=0;
	double step=1/b;

	for(i=point-1;i>=0;i--)
	{
		step*=b;

		num+=(s[i])*step;
	}

	step=1;

	for(i=point+1;i<l;i++)
	{
		step/=b;

		num+=(s[i])*step;
	}

	printf("%f\n",num);

	return(0);
}
