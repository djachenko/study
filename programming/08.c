#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

// words can be separated by more than one space

int main(int argc, char *argv[])
{
	setlocale(LC_ALL,"");

	FILE *f=fopen(argv[1],"r");
	if (!f)
	{
		perror("fopen");
		return 1;
	}
//	freopen("output.txt","wt",stdout);

	char c;
	
	int chars=0;
	int words=0;
	int strings=0;
	int state=1;

	for ( ; ; )
	{
		c=fgetc(f);
		if (c == EOF) break;

		chars++;
		
		if (c=='\n') strings++;
		
		if (state && !isspace(c))
		{
			words++;
			state=0;
		}

		if (!state && isspace(c)) state=1;
	}

	printf("%d\n",chars);
	printf("%d\n",words);
	printf("%d\n",strings);
	
	return(0);
}
