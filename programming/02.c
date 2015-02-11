#include <stdio.h>

int main()
{
	int a=40;
	int b=100;

	if (a<b) 
	{
		int c=a;
		a=b;
		b=c;
	}

	while (a%b>0)
	{
		a=a%b;

		if (a<b) 
		{
			int c=a;
			a=b;
			b=c;
		}
	}
	printf("%d\n",b);
	return 0;
}
