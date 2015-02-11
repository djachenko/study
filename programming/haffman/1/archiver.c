#include <stdio.h>
#include <string.h>

#include "list.h"
#include "tree.h"
#include "const.h"
#include "types.h"

void encode(struct node * root, struct list * code)
{
	if (root->value!=-1)
	{
		printf("(%d)",root);
		print_list(code);
		codes[root->value]=list_dup(code);
		return;
	}

	if (root->left)
	{
		list_add(&code,'0');

		putchar('0');

		encode(root->left, code);

		list_tailget(&code);
	}

	if (root->right)
	{
		list_add(&code,'1');

		putchar('1');

		encode(root->right, code);

		list_tailget(&code);
	}
}

void archiver(FILE * source)//���������� ������� ���������
{
	int c;
	int i;

	fseek(source, 0, SEEK_SET);//����� ������� � ������ �����

	while ((c=fgetc(source))!=EOF)//���� �� ��������� ����� �����
	{
		list_cat(&buffer,codes[c]);//�������� � ����� ���� �������
		buffer_size+=list_len(codes[c]);

		while (buffer_size>=8)//���� ������ �������
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

			putchar(symbol);//��� �����
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

	putchar(symbol);
}

void archivize(char * source_name)
{
	FILE * source=fopen(source_name,"w");

	{
		char c;

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

		struct node * root=new_tree(leaves,n);//�������� ������ ��������� ��������

		struct list * code=NULL;

		encode(root,code);//������� ����� �������� (������, ������� ������� - ������ �����)

		cut_tree(root);
	}

	char archive_name[256]={0};

	printf("Enter name of your archive: ");
	scanf("%s",archive_name);

	freopen(archive_name,"w",stdin);
	printf("%s ",source_name);

	print(root,0);

	putchar(' ');

	archiver(source);

	fclose(source);
}
