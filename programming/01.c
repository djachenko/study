#include <stdio.h>

main ()
{
	int n;

	scanf("%d",&n);
	
	int i=0;
	int k=1;
	int l;
	
	for ( ;n>0;n--)
	{
		printf("%d ",i);
		l=k+i;
		i=k;
		k=l;
	}

	printf("\n");

	return 0;

}
