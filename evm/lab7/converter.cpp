#include <stdio.h>

int main(int argc, char ** argv)
{
	freopen(argv[1],"r",stdin);
	
	for(int c=getchar(); c!=EOF; c=getchar() )
	{
		if (c=='.')
		{
			putchar(',');
		}
		else
		{
			putchar(c);
		}
	}

	return 0;
}
