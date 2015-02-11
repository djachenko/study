#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "types.h"

#define size 257

void fprint_tree(struct node * a, FILE * dest)//выводит скобочную запись дерева
{
	if (!a)
		return;

	fputc(' ',dest);
	fputc('(',dest);

	if (a->value!=-1)
		fprintf(dest,"!%c",a->value);

	fprint_tree(a->left,dest);

	fprint_tree(a->right,dest);

	fputc(')',dest);
}

void print_tree(struct node * a)
{
	fprint_tree(a,stdout);
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

struct node * fread_tree(FILE * stream)//чтение дерева из потока
{
	int c=0;

	struct node * root=new_node();

	while (c!='(')//пропуск левых символов. внутри _правильно составленного_ дерева не работает, но хуже не будет
	{
		c=fgetc(stream);
	}

	c=fgetc(stream);//чтение символа-идентификатора

	switch (c)//автомат с концами
	{
		case ' '://обозначение того, что значение пустое, надо запустить
			root->left=fread_tree(stream);
			break;
		case '!'://а тут символ. запускать ничего не надо, ибо это свойство кода
			c=fgetc(stream);//прочитал
			root->value=c;//добавил
			break;
	}

	c=fgetc(stream);//следующий идентификатор

	if (c==' ')//надо еще раз запустить
	{
		root->right=fread_tree(stream);
		c=fgetc(stream);//чтение очередного идентификатора. можно без него, но автомат запутается
	}

	return root;
}

struct node * read_tree()//запуск fread_tree относительно stdin
{
	return fread_tree(stdin);
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

static int max(int a, int b)
{
	if (a>b)
		return a;

	return b;
}

int tree_height(struct node * root)
{
	if (!root)
	{
		return 0;
	}

	return max(tree_height(root->left),tree_height(root->right))+1;
}
