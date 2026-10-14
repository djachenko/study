//набор функций для работы с деревом

#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#define size 257

void print(struct node * a)//распечатка дерева
{
	if (!a)
		return;

	putchar('(');

	if (a->value)
		printf("%c",a->value);

	print(a->left);
	print(a->right);

	putchar(')');
}

struct node * new_node(void)//возвращает аллоцированный и зануленный узел. Тупо для удобства
{
	struct node * item=malloc(sizeof(struct node));

	item->left=NULL;
	item->right=NULL;
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

struct node * new_tree(int freq[size], struct node * leaves[size], int n)//создает дерево в соответствии с частотами из листьев
{
	int i;
	struct node * root=NULL;

	if (n==1)//если в файле только один символ
	{
		root=new_node();
		root->value=-1;
		root->right=NULL;

		for (i=0;i<size;i++)
		{
			if (leaves[i])//нахождение этого одинокого листа
			{
				root->left=leaves[i];
				break;
			}
		}

		return root;
	}

	while (n>=2)//если два и больше (рассчитано на отправку как влево, так и вправо)
	{
		int min1=-1;//первый...
		int mini1=-1;
		int min2=-1;//и второй минимумы
		int mini2=-1;//а это индексы

		for (i=0;i<size;i++)//их нахождение
		{
			if (freq[i] && (freq[i]<min1 || min2==-1))//какой-то бред, но работает
			{
				min2=min1;
				mini2=mini1;

				min1=freq[i];
				mini1=i;
			}
		}

		freq[mini1]+=freq[mini2];//перераспределение частот
		freq[mini2]=0;

		struct node * temp=new_node();

		temp->value=-1;//потому что 0 - символ конца
		temp->left=leaves[mini1];//связь собственно
		temp->right=leaves[mini2];

		leaves[mini1]=temp;//подставка полученного узла в массив, чтобы работать с ним, как с объединением листьев
		leaves[mini2]=NULL;//а второй просто выбрасываем

		n--;//листьев стало на один меньше (вместо второго теперь нода)

		if (n==1)
		{
			root=temp;//если один лист, то это нода, к которой привязано все остальное. ну и в корень ее
			break;
		}
	}

	return root;
}
