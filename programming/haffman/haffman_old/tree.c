//����� ������� ��� ������ � �������

#include <stdlib.h>
#include <stdio.h>

#include "types.h"

#define size 257

void print(struct node * a)//���������� ������
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

struct node * new_node(void)//���������� �������������� � ���������� ����. ���� ��� ��������
{
	struct node * item=malloc(sizeof(struct node));

	item->left=NULL;
	item->right=NULL;
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

struct node * new_tree(int freq[size], struct node * leaves[size], int n)//������� ������ � ������������ � ��������� �� �������
{
	int i;
	struct node * root=NULL;

	if (n==1)//���� � ����� ������ ���� ������
	{
		root=new_node();
		root->value=-1;
		root->right=NULL;

		for (i=0;i<size;i++)
		{
			if (leaves[i])//���������� ����� ��������� �����
			{
				root->left=leaves[i];
				break;
			}
		}

		return root;
	}

	while (n>=2)//���� ��� � ������ (���������� �� �������� ��� �����, ��� � ������)
	{
		int min1=-1;//������...
		int mini1=-1;
		int min2=-1;//� ������ ��������
		int mini2=-1;//� ��� �������

		for (i=0;i<size;i++)//�� ����������
		{
			if (freq[i] && (freq[i]<min1 || min2==-1))//�����-�� ����, �� ��������
			{
				min2=min1;
				mini2=mini1;

				min1=freq[i];
				mini1=i;
			}
		}

		freq[mini1]+=freq[mini2];//����������������� ������
		freq[mini2]=0;

		struct node * temp=new_node();

		temp->value=-1;//������ ��� 0 - ������ �����
		temp->left=leaves[mini1];//����� ����������
		temp->right=leaves[mini2];

		leaves[mini1]=temp;//��������� ����������� ���� � ������, ����� �������� � ���, ��� � ������������ �������
		leaves[mini2]=NULL;//� ������ ������ �����������

		n--;//������� ����� �� ���� ������ (������ ������� ������ ����)

		if (n==1)
		{
			root=temp;//���� ���� ����, �� ��� ����, � ������� ��������� ��� ���������. �� � � ������ ��
			break;
		}
	}

	return root;
}
