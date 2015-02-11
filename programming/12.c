#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// should not find user dya

int check(char *s,char *name)
{
	int l=s-strstr(s,":");
	
	int i;

	for(i=0;i<l;i++)
		if (s[i]!=name[i]) return(1)

    	int k;

    	i=0;
	k=0;

    	while(k<4)
    	{
        	if (s[i]==':') k++;

        	i++;
    	}

	while(s[i]!=',' && s[i]!=':')
    	{
        	putchar(s[i]);
        	i++;
    	}

    	putchar('\n');

    	return(0);
}

int main()
{
   	FILE *f=fopen("/etc/passwd","r");

    	char s[10000];
    	char src[10000];

    	scanf("%s",src);

   	int d;
	char *x;

	do
	{
    		x=fgets(s,10000,f);
		d=check(s,src);
	}
    	while(d && x);

	if (d) printf("No such user\n");

	fclose(f);

    	return 0;
}
