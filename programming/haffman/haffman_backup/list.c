#include <stdlib.h>
#include <stdio.h>//print_list

#include "types.h"

struct list * new_list(void)
{
	struct list * item=malloc(sizeof(struct list));

	item->value=0;
	item->next=NULL;

	return item;
}

int empty(struct list * a)
{
	if (a)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void print_list(struct list * src)
{
	struct list * p=src;

	while (p)
	{
		printf("%c",p->value);
		p=p->next;
	}

	putchar('\n');
}

void list_add(struct list ** to, int a)
{
	struct list * p=*to;

	while (p && p->next)
	{
		p=p->next;
	}

	if (p)
	{
		p->next=new_list();
		p=p->next;
	}
	else
	{
		p=new_list();
		*to=p;
	}

	p->value=a;
}

struct list * list_dup(struct list * src)
{
	if (!src)
		return NULL;

	struct list * result=new_list();
	struct list * p=result;
	struct list * q=NULL;

	p->value=src->value;

	q=p;
	p=p->next;
	src=src->next;

	while (src)
	{
		p=new_list();
		p->value=src->value;
		q->next=p;

		q=p;
		src=src->next;
	}

	return result;
}

void list_cat(struct list ** to, struct list * from)
{
	if (!(*to))
	{
		*to=list_dup(from);
		return;
	}

	struct list * p=*to;

	while (p->next)
	{
		p=p->next;
	}

	p->next=list_dup(from);
}

int list_get(struct list ** source)
{
	if (!(*source))
		return 0;

	int a=(*source)->value;
	struct list * p=*source;

	*source=(*source)->next;

	free(p);

	return a;
}

int list_nget(struct list ** source, int n)
{
	if (!(*source))
	{
		return 0;
	}

	if (n==1)
	{
		return list_get(source);
	}

	if (n==2)
	{
		return list_nget(&((*source)->next), (n-1));

		(*source)->next=NULL;

		return 0;
	}

	return list_nget(&((*source)->next), n-1);
}

int list_tailget(struct list ** source)
{
	return list_nget(source, list_len(*source));
}


int list_len(struct list * a)
{
	int len=0;
	struct list * p=a;

	while (p)
	{
		len++;
		p=p->next;
	}

	return len;
}

void list_clear(struct list ** source)
{
	if (!(*source))
		return;

	list_clear(&((*source)->next));

	free(*source);

	*source=NULL;

	return;
}
