#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "types.h"

#define size 257

void fprint_tree(struct node * a, FILE * dest)//������� ��������� ������ ������
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

struct node * fread_tree(FILE * stream)//������ ������ �� ������
{
	int c=0;

	struct node * root=new_node();

	while (c!='(')//������� ����� ��������. ������ _��������� �������������_ ������ �� ��������, �� ���� �� �����
	{
		c=fgetc(stream);
	}

	c=fgetc(stream);//������ �������-��������������

	switch (c)//������� � �������
	{
		case ' '://����������� ����, ��� �������� ������, ���� ���������
			root->left=fread_tree(stream);
			break;
		case '!'://� ��� ������. ��������� ������ �� ����, ��� ��� �������� ����
			c=fgetc(stream);//��������
			root->value=c;//�������
			break;
	}

	c=fgetc(stream);//��������� �������������

	if (c==' ')//���� ��� ��� ���������
	{
		root->right=fread_tree(stream);
		c=fgetc(stream);//������ ���������� ��������������. ����� ��� ����, �� ������� ����������
	}

	return root;
}

struct node * read_tree()//������ fread_tree ������������ stdin
{
	return fread_tree(stdin);
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
