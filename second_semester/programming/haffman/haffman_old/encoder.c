#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "list.h"

struct list * codes[257];//���� ��������. �������� ��������
int code_lens[257];//����� ����� ��������
static struct list * buffer;//�����
static int buffer_size;//������ ������

void to_buffer(int c)//�������� � ������ ���� �������
{
	listcat(buffer,listdup(codes[c]));
	buffer_size+=code_lens[c];//����������� �������
}

void print_code(void)//����� ����� ������ � �������� ���� (���� ������ ������ �� ������)
{
	if (buffer_size<8)//�� ������ �� ������
	{
		return;
	}

	int i=8;
	int c=0;

	while (i)//������� � �������� �������
	{
		c=c*2+buffer->value;

		struct list * p=buffer;
		buffer=buffer->next;
		free(p);
	}

	putchar(c);//�����
}

void encoder(struct node * a, struct list * code)//������� ����� �������� �� ������ (code - �������� ���� �� ���� �� �����)
{
	if (!a)//� ���� ����
	{
		return;
	}

	if (a->value!=-1)//�, ������!
	{
		codes[a->value]=code;//����� ������ ��������� � �� �������
		code_lens=listlen(code);//����� ���� �������
		return;
	}

	struct list * b=new_list();

	b->value=0;//��� �����
	encoder(a->left,listcat(code,b));//������������� ���� ��� � ��� ���������� ����

	b->value=1;
	encoder(a->left,listcat(code,b));

	return;
}

void archiver(char * source_name, char * archive_name)//��������� ��������� (������ � ����)
{
	FILE * source=fopen(source_name,"r");//��������
	freopen(archive_name,"w",stdout);//�������� ����

	printf("%s ",source_name);//����� ��������, ���� ����� ������������
	print(root);//����� ������ ��������� �������
	putchar(' ');//�����������

	buffer_size=0;//��������, ��� ������

	int c;

	while (1)
	{
		c=fgetc(source);//���������...

		to_buffer(c);//...����������...

		print_code();//...� ����������� ������
	}
}
