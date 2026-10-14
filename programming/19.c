#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	struct item
	{
		char word[11];
		int count;
		struct item *next;
	};

	struct item *head=NULL;

	FILE *f=fopen("19.txt","r");

	char s[11];

	while(fscanf(f,"%s",s)==1)
	{
		struct item *p=head;
		struct item *q=NULL;

		int d;

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
	}

	struct item *p=head;
	struct item *q;

	while(p)
	{
		printf("\"%s\": %d\n",p->word,p->count);
		q = p;
		p=p->next;
		free(q);
	}

	fclose(f);
	return 0;
}
