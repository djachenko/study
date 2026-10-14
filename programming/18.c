#include <stdio.h>
#include "alloc.h"

int main()
{
	struct item
	{
		int data;
		struct item *next;
	};

	struct item *head=NULL;

	FILE *f=fopen("18.txt","r");

	int a;

	while(fscanf(f,"%d",&a)==1)
	{
		printf("read: %d\n", a);
		struct item *p=head;
		struct item *q=NULL;

		while(p && p->data<=a)
		{
			q=p;
			p=p->next;
		}

		p=myalloc(sizeof(struct item));

		p->data=a;
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

	struct item *p=head, *q;

	while(p)
	{
		printf("%d ",p->data);
		q = p;
		p=p->next;
		myfree(q);
	}
	putchar('\n');

	fclose(f);
	return 0;
}
