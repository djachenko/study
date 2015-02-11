#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#define size 257

void print(struct node * a)//������� ��������� ������ ������
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

void cut_tree(struct node * a)//������ ������
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
	if (n==1)//���� ���� �������. ��, ����� ����� ��������
	{
		int i;

		for (i=0;;i++)//���������� ���� ������ ��������
		{
			if (leaves[i])
			{
				break;
			}
		}

		struct node * root=new_node();
		struct node * a=new_node();
		a->value=i;

		root->right=a;//� � ������ ���

		return root;
	}
	else//� ��� �� ������...
	{
		qsort(leaves,256,sizeof(* leaves),compare_first);//������� �������� ����������� � �����

		while (n>1)
		{
			qsort(leaves,n,sizeof(* leaves),compare);//���������� �� �������

			struct node * a=new_node();//�������� ��������� ����

			a->left=leaves[n-2];//������������ ���� �����
			a->right=leaves[n-1];//� ����������� ���������
			a->freq=leaves[n-2]->freq+leaves[n-1]->freq;//� ������������ �� ������ � ������

			leaves[n-2]=a;//������ ������
			leaves[n-1]=NULL;//� ����� �������
			n--;
		}

		return leaves[0];//������� ���� �������, ��� � ����������
	}
}
