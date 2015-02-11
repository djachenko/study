//helpful functions
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "const.h"
#include "types.h"
#include "parser.h"

static int index;

int sgetc(struct stream * a)
{
	int c;

	c=a->s[a->index];

	a->index++;

	return c;
}

void unsgetc(struct stream * a)
{
	a->index--;
}

void reset(struct stream * a)
{
	a->index=0;
}

int func(int a)
{
	switch (a)
	{
		case '(':
			return -2;
		case ')':
			return -1;
		case '+':
			return 1;
		case '-':
			return 2;
		case '*':
			return 3;
		case '/':
			return 4;
		case '^':
			return 5;
	}


	if (strcmp((char *)a,"log")==0)
		return 6;
	if (strcmp((char *)a,"sin")==0)
		return 7;
	if (strcmp((char *)a,"cos")==0)
		return 8;
	if (strcmp((char *)a,"sqrt")==0)
		return 9;
	if (strcmp((char *)a,"abs")==0)
		return 10;

	return 0;
}

int check()
{
	int i;
	int k=0;

	struct hashtable * p;

	for (i=0;i<255;i++)
	{
		if (vars[i])
		{
			p=vars[i];

			while (p)
			{
				if (p->value && !constance(p->variable))
					return 1;

				p=p->next;
			}
		}
	}

	return k;
}

void clear()
{
	int i;

	struct hashtable * p;
	struct hashtable * q;

	for (i=0;i<255;i++)
	{
		if (vars[i])
		{
			p=vars[i];
			q=NULL;

			while (p)
			{
				q=p;
				p=p->next;
				free(q);
			}

			vars[i]=NULL;
		}
	}

	return;
}

void spacescanf(char * s)
{
	int c;
	int i=0;

	while ((c=getchar())!='\n')
	{
		s[i]=c;
		i++;
	}
	s[i]=0;

	int j=0;
	int l=strlen(s);

	char temp[256]={0};

	for (i=0;i<l;i++)
	{
		if (s[i]==' ')
			continue;

		temp[j]=s[i];
		j++;
	}

	strcpy(s,temp);
}
