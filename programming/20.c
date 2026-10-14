#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 997

int hash(char *s)
{
	int step=1;
	int sum=0;
	int i;

	for (i = 0; s[i]; i++)
	{
		sum = sum * 37 + s[i];

		sum%=N;
	}
	printf("hash(%s) = %d\n", s, sum);

	return(sum);
}

int main()
{
	struct item
	{
		char word[11];
		int count;
		struct item *next;
	};

	struct item *hash_table[N];

	int i;

	for (i=0;i<N;i++)
		hash_table[i]=NULL;

	FILE *f=fopen("20.txt","r");

	char s[100];

	while(fscanf(f,"%s",s)==1)
	{
		int value=hash(s);

		struct item *head=hash_table[value];

		struct item *p=head;
		struct item *q=NULL;

		int d=1;

		while(p && (d=strcmp(s,p->word))<0)
		{
			q=p;
			p=p->next;
		}

		if (d==0) p->count++;

		if (d>0 || !p)
		{

			p=malloc(sizeof(struct item));

			strcpy(p->word,s);
			p->count=1;
			if (!q)
			{
				p->next=head;
				head=p;
			}
			else
			{
				p->next=q->next;
				q->next=p;
			}
		}

		hash_table[value]=head;
	}

	for (i=0;i<N;i++)
	{
		struct item *p=hash_table[i], *q;
		int c = 0;

		while(p)
		{
			printf("\"%s\": %d\n",p->word,p->count);
			q = p;
			p=p->next;
			free(q);
			c++;
		}
		if (c > 0)
		{
			printf("idx %d: count %d\n", i, c);
		}

	}

	fclose(f);

	return(0);
}
