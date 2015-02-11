#include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *f=fopen(argv[1],"rb");
	FILE *g=fopen(argv[2],"wb");

	char c;

	while((c=fgetc(f))!=EOF)
	{
		fputc(c,g);
	}

	fclose(f);
	fclose(g);

	return(0);
}
