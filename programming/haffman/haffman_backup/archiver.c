#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"
#include "const.h"
#include "types.h"

static void make_codes(struct node * root, struct list * code)
{
	if (root->value!=-1)
	{
		codes[root->value]=list_dup(code);
		return;
	}

	if (root->left)
	{
		list_add(&code,'0');

		make_codes(root->left, code);

		list_tailget(&code);
	}

	if (root->right)
	{
		list_add(&code,'1');

		make_codes(root->right, code);

		list_tailget(&code);
	}
}

static void clear()
{
	int i;

	for (i=0;i<256;i++)
	{
		if (codes[i])
		{
			struct list * p=codes[i];
			struct list * q=NULL;

			while (p)
			{
				q=p;
				p=p->next;
				free(q);
			}
		}
	}
}

static void encoder(FILE * source, FILE * archive)//���������� ������� ���������
{
	int c;
	int i;

	fseek(source, 0, SEEK_SET);//����� ������� � ������ �����

	while ((c=fgetc(source))!=EOF)//���� �� ��������� ����� �����
	{
		list_cat(&buffer,codes[c]);//�������� � ����� ���� �������
		buffer_size+=list_len(codes[c]);

		while (buffer_size>=8)//���� ������ ������� �� �������� ����� (���� �� �������, �������� �� ��������� ����)
		{
			char symbol_code[9]={0};//������ � ����� ��������������� �������

			for (i=0;i<8;i++)
			{
				symbol_code[i]=list_get(&buffer);//������������ �� ������ �� "����"
			}

			buffer_size-=8;

			int step=1;
			int symbol=0;

			for (i=7;i>=0;i--)//����������� ����������� � ���� ������

			{
				symbol+=step*(symbol_code[i]-'0');
				step*=2;
			}

			fputc(symbol,archive);//��� �����
		}
	}

	char symbol_code[9]={0};

	if (buffer_size)
	{
		for (;buffer_size<8;)
		{
			list_add(&buffer,'0');
			buffer_size++;
		}
	}

	for (i=0;i<8;i++)
	{
		symbol_code[i]=list_get(&buffer);//������������ �� ������ �� "����"
	}

	buffer_size-=8;

	int step=1;
	int symbol=0;

	for (i=7;i>=0;i--)//����������� ����������� � ���� ������
	{
		symbol+=step*(symbol_code[i]-'0');
		step*=2;
	}

	fputc(symbol,archive);
}

int compare_first (const void * a, const void * b)
{
	  return ( *(int *)b - *(int *)a);
}

int compare (const void * a, const void * b)
{
	  return ( (*(struct node **)b)->freq - (*(struct node **)a)->freq );
}

static struct node * make_tree(FILE * source)
{
	int c;

	struct node * leaves[256];//������� �������� ����� � �������

	int i;

	for (i=0;i<256;i++)
		leaves[i]=NULL;

	int n=0;//���-�� ��������� ��������

	while((c=fgetc(source))!=EOF)
	{
		if (!leaves[c])//���� ������ ��� �� ����
		{
			n++;
			leaves[c]=new_node();
			leaves[c]->value=c;
		}

		leaves[c]->freq++;//��������� �������
	}

	if (n==0)
	{
		struct node * root=new_node();

		root->freq=0;

		return root;
	}

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

void archivize(char source_name[256], char archive_name[256])
{
	FILE * source=fopen(source_name,"r");

	if (!source)
	{
		printf("Error: source file wasn't opened\n");
		return;
	}

	if (!archive_name[0])
	{
		printf("Enter name of your archive, please: ");
		scanf("%s", archive_name);
	}

	FILE * archive=fopen(archive_name,"w");

	fprintf(archive,"%s ",source_name);

	struct node * root=make_tree(source);

	fprintf(archive,"%d ",root->freq);

	if (root->freq==0)
	{
		cut_tree(root);

		fclose(source);
		fclose(archive);

		return;
	}

	make_codes(root,NULL);

	fprint_tree(root,archive);

	cut_tree(root);

	encoder(source,archive);

	fclose(source);
	fclose(archive);

	clear();
}
