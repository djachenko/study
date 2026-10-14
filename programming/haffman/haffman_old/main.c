#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "tree.h"

#define size 257

struct node * root=NULL;//корень дерева с символами

int main()
{
	FILE * source=fopen("input.txt","r");

	int freq[size]={0};//массив частот

	int c;
	int n=0;

	while (1)//задание частот
	{
		c=fgetc(source);

		if (c==-1)
			break;

		if (!freq[c])
		{
			n++;//кол-во различных символов в файле
		}

		freq[c]++;
	}

	int i;

	struct node * leaves[size];//массив под листья дерева

	for (i=0;i<size;i++)//формирование листьев
	{
		if (freq[i])//нет символа - на кой лист?
		{
			leaves[i]=new_node();

			leaves[i]->value=i;
			leaves[i]->left=NULL;
			leaves[i]->right=NULL;
		}
	}

	root=new_tree(freq,leaves,n);//создание дерева

	print(root);

	cut_tree(root);//срубить дерево

	return 0;
}
