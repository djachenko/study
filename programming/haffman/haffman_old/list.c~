//типа библиотеки для списков. полезная, кстати, хрень.

#include <stdlib.h>

#include "types.h"

struct list * new_list(void)//возвращает зануленный элемент списка
{
	struct list * item=malloc(sizeof(struct list));

	item->value=0;
	item->next=NULL;

	return item;
}

struct list * listcat(struct list * src, struct list * dst)//склеивает первый список со вторым. первый не трогается
{
	struct list * p=dst;

	while (p)
	{
		p=p->next;
	}

	p->next=listdup(src);

	return dst;
}

struct list * listdup(struct list * src)//дублирует список и возвращает копию
{
	struct list * p=src;
	struct list result=NULL;
	struct * q=result;

	while (p)
	{
		q=new_list();
		q->value=p->value;

		p=p->next;
		q=q->next;
	}

	return result;
}

int listlen(struct list * a)//считает длину списка
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
