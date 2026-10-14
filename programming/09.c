#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main()
{
#define x 1000

	setlocale(LC_ALL, "");

	char s[x];
	s[0]=0;
	char s1[x];

	char c='f';

	while(c!='\n')
	{
		scanf("%s%c",s1,&c);
		strcat(s,s1);
	}

	int l=0;
	int r=strlen(s)-1;

	do
	{
	    while (s[l] && !isalpha(s[l])) l++;
	    while (s[r] && !isalpha(s[r])) r--;

		if (s[l]!=s[r])
		{
			printf("No %d %d %c %c\n",l,r,s[l],s[r]);
			return(0);
		}

		l++;
		r--;
	}
	while (l<=r);

	printf("Yes\n");

	return(0);
}
