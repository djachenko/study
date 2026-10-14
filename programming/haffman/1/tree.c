#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#define size 257

void print(struct node * a)//выводит скобочную запись дерева
{
	if (!a)
		return;

	putchar('(');

	if (a->value!=-1)
		printf("%c",a->value);

	print(a->left);
	print(a->right);

	putchar(')');
}

struct node * new_node(void)
{
	struct node * item=malloc(sizeof(struct node));

	item->left=NULL;
	item->right=NULL;
	item->freq=0;
	item->value=-1;

	return item;
}

void cut_tree(struct node * a)//сносит дерево
{
	if (!a)
		return;

	cut_tree(a->left);
	cut_tree(a->right);

	free(a);

	return;
}

int compare_first (const void * a, const void * b)
{
	  return ( *(int *)b - *(int *)a);
}

int compare (const void * a, const void * b)
{
	  return ( (*(struct node **)b)->freq - (*(struct node **)a)->freq );
}

struct node * new_tree(struct node * leaves[256], int n)
{
	if (n==1)//если один элемент. Ну, тупой такой алгоритм
	{
		int i;

		for (i=0;;i++)//нахождение ТОГО САМОГО элемента
		{
			if (leaves[i])
			{
				break;
			}
		}

		struct node * root=new_node();
		struct node * a=new_node();
		a->value=i;

		root->right=a;//и в дерево его

		return root;
	}
	else//а тут их больше...
	{
		qsort(leaves,256,sizeof(* leaves),compare_first);//нулевые элементы спихиваются в конец

		while (n>1)
		{
			qsort(leaves,n,sizeof(* leaves),compare);//сортировка по частоте

			struct node * a=new_node();//создание связущего узла

			a->left=leaves[n-2];//выдергивание двух узлов
			a->right=leaves[n-1];//с наименьшими частотами
			a->freq=leaves[n-2]->freq+leaves[n-1]->freq;//и суммирование их частот в связку

			leaves[n-2]=a;//замена одного
			leaves[n-1]=NULL;//и вынос другого
			n--;
		}

		return leaves[0];//остался один элемент, его и возвращаем
	}
}
