#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f=fopen("input.txt","r");
    freopen("public_html/output.html","w",stdout);

    int td=0;
    int c;

    printf("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=koi8-r\"></head><body>\n");
    printf("<table border=\"1\">\n<tr>\n<td>\n");

	while(c!=EOF)
	{
		c=fgetc(f);

		if (td==0)
		{
			if (c=='\"') td=1;
			if (c==',') printf("\n</td>\n<td>\n");
			if (c=='\n') printf("\n</td>\n</tr>\n<tr>\n<td>\n");

			if (c!='\"' && c!=',' && c!='\n' && c!=EOF) putchar(c);
		}
		else

		if (td)
		{
			if (c == '\n') printf("<br>");
			if (c=='\"')
			{
				c=fgetc(f);

				if (c=='\"') putchar('\"');
				if (c==',')
				{
					printf("\n</td>\n<td>\n");
					td=0;
				}

				if(c!='\"' && c!=',' && c!=EOF) putchar(c);
			}
			else if (c!=EOF) putchar(c);
		}
	}

    printf("</td>\n</tr>\n</table></body></html>\n");

    fclose(f);

    return 0;
}
