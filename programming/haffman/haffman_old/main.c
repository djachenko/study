#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "tree.h"

#define size 257

struct node * root=NULL;//������ ������ � ���������

int main()
{
	FILE * source=fopen("input.txt","r");

	int freq[size]={0};//������ ������

	int c;
	int n=0;

	while (1)//������� ������
	{
		c=fgetc(source);

		if (c==-1)
			break;

		if (!freq[c])
		{
			n++;//���-�� ��������� �������� � �����
		}

		freq[c]++;
	}

	int i;

	struct node * leaves[size];//������ ��� ������ ������

	for (i=0;i<size;i++)//������������ �������
	{
		if (freq[i])//��� ������� - �� ��� ����?
		{
			leaves[i]=new_node();

			leaves[i]->value=i;
			leaves[i]->left=NULL;
			leaves[i]->right=NULL;
		}
	}

	root=new_tree(freq,leaves,n);//�������� ������

	print(root);

	cut_tree(root);//������� ������

	return 0;
}
