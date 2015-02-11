#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"//pop � calc
#include "types.h"
#include "functions.h"//sgetc
#include "counter.h"
#include "parser.h"
#include "error.h"

int sign=1;//number which defines sign of operand
int errorcode=0;//��� ������
int state=0;//��� ��������� �������� � �������, �� ���, ��� ��� ��������� ���.
FILE * logfile;//���-����

struct hashtable * vars[255];//hashtable of variables

double calc(struct stream * stream)//������ ��������.
{
	if (strcmp(stream->s,"")==0)//�������� �� ������ ���������
	{
		errorcode=5;
		return 0;
	}

	{//�������� ������
		int i;
		int l=strlen(stream->s);
		int k=0;

		for (i=0;i<l;i++)
		{
			if (stream->s[i]=='(')
				k++;
			if (stream->s[i]==')')
				k--;

			if (k<0)
			{
				break;
			}
		}

		if (k!=0)
		{
			errorcode=6;
			return 0;
		}
	}//�������� ������

	if (strchr(stream->s,'='))
	{
		errorcode=6;
		return 0;
	}

	int c;
	state=0;//������� ���������
	sign=1;

	while (!errorcode)//������ ���������
	{
		c=sgetc(stream);

		if (c==0)
			break;

		parser_right(c,stream);
	}

	if (errorcode)
		return 0;

	if (state%3!=0)
	{
		errorcode=7;
		return 0;
	}

	while (stream->funcs)//����������� ��, ��� �� � ������� (������ ��������� ��������)
	{
		counter(&(stream->ints),pop(&(stream->funcs)));
	}

	return d_pop(&(stream->ints));
}

int main()
{
	int i;

	for (i=0;i<255;i++)
		vars[i]=NULL;

	logfile=fopen("log.txt","a");
	fprintf(logfile,"start\n");

	while(1)
	{
		char s[256]={0};
		errorcode=0;//�������� ��� ������

		printf("> ");

		spacescanf(s);//������ ��������� ������

        fprintf(logfile,"> %s\n",s);

		if (strcmp(s,"")==0)//�������� �� ������ ����
		{
			errorcode=1;
			error();
			continue;
		}

		struct stream mainstream;//source of non-parsed sentence. ���������� �������� ��� ����� �����, ��� ���-�� � clear ������ ���� ����

		mainstream.index=0;
		mainstream.ints=NULL;
		mainstream.funcs=NULL;

		//��� ������ ����
		if (strcmp(s,"stop")==0 || strcmp(s,"stopit")==0)//������� ���������
		{
			clear_stream(&mainstream);//������� ������
			clear_hashtable();//������� ������� ����������
			fclose(logfile);
			return 0;
		}

		char * is=strchr(s,'=');//���������� ����� ��������� (���� ��� - NULL)

		if (!is)//����� ���, ������ ���������
		{
			strcpy(mainstream.s,s);//���������� ��� ������ � �����

			double answer=calc(&mainstream);

			if (!errorcode)
			{
				printf("%lf\n",answer);//����� ����������
				fprintf(logfile,"< %lf\n",answer);//����� ���������� � ���
			}
		}
		else//�������� ��� ����������
		{
			int l=is-s;//����� ����� �����
			char name[256]={0};//����� ��� ��� ����������

			strncpy(name,s,l);//����������� ����� ����� � "���"

			for (i=0;i<l;i++)//�������� ����� �� ������� ������
			{
				if (!isalpha(name[i]) && !isdigit(name[i]))
				{
					errorcode=2;//���� �� ���� ���� �����
					break;
				}
			}

			if (errorcode || func((int)name) || constance(name)!=0.0)//���� ���� ���� ����, ���� �������, ���� ���������
			{
				errorcode=2;
			}//��� ��, ������� ���

			if (!errorcode)//���� ��� ������ � �� ���������
			{
				strcpy(mainstream.s,is+1);//������ ����� (���������) � �����

				double answer=calc(&mainstream);//��������� � ���������

				if (!errorcode)
				{
					printf("%lf\n",answer);//����� ����������
					fprintf(logfile,"< %lf\n",answer);
					parser_left(name)->value=answer;//� ������� �������� ��������� � ����������
				}
			}
		}

		clear_stream(&mainstream);

		error();//�������������
	}

	fclose(logfile);

	return 0;
}
