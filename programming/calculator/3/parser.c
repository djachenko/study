#include <stdio.h>//ask
#include <ctype.h>//parser (����������)
#include <math.h>//��������� �� ��� ��������� -1
#include <stdlib.h>//�������� ����������
#include <string.h>//�������� ����������

#include "functions.h"
#include "const.h"
#include "stack.h"

static double constance(char * a)
{
	if (strcmp(a,"pi")==0)
		return acos(-1);
	if (strcmp(a,"e")==0)
		return 2.71828;

	return 0.0;
}

static int priority(int c)
{
	if (c==-1 || c==-2)
		return -1;
	if (c==1 || c==2)
		return 1;
	if (c==3 || c==4)
		return 2;
	if (c==5)
		return 3;
	if (c>=6 && c <=10)
		return 4;

	return 0;
}

static int hash(char * src)
{
	int res=0;
	int i=0;

	while (src[i])
	{
		res=(res*27+src[i])%255;
		i++;
	}

	return res;
}

static double ask(char * name)
{
	double a;

	printf("Input value of variable %s, please: ",name);
	scanf("%lf",&a);

	return a;
}

void parser(int c, struct stream stream)
{
	if (isdigit(c))//��������� �����, �� ���� �������� �����
	{
		double num=0;//������� ���������� ��� ����� (�������)

		while (isdigit(c))//���� ����� �� �����������
		{
			num=num*10+c-'0';//���������� �����
			c=sgetc(stream);
		}

		if (c=='.' || c==',')//������� � ������� �����
		{
			int dot=10;//���������
			c=sgetc(stream);

			while (isdigit(c))//�� ��, ��� � ����
			{
				num+=(c-'a')*1.0/dot;

				dot*=10;
				c=sgetc(stream);
			}
		}

		num*=sign;

		push(&ints_stack,num);//�������� � �������� ����
		unsgetc(stream);

		sign=1;
		status=1;

		return;
	}

	if (isalpha(c))//���� ��������� �����, �� ���� ����������
	{
		char name[255]={0};
		int i=0;

		while (isalpha(c))//������������ ����� ����������
		{
			name[i]=c;
			i++;
			c=sgetc(stream);
		}

		unsgetc(stream);

		if (func((int)name))//��������, �� ������� �� ��� (���������� sin, cos � �.�. �� �����������)
		{
			push(&func_stack,func((int)name));//���� ��, �� �������� � ���� �������
			return;
		}

		//�������� ������� ��������, ��� �� �������

		int h=hash(name);

		struct hashtable *p=vars[h];
		struct hashtable *q=NULL;

		int d;

		while (p && (d=strcmp(p->variable,name))<0)
		{
			q=p;
			p=p->next;
		}

		if (d==0)//���������� ��� ���� (�������� ��� ������)
		{
			push(&ints_stack,p->value);
			return;
		}

		if (d>0 || !p)
		{

			p=malloc(sizeof(*p));
			strcpy(p->variable,name);

			if (constance(name)!=0.0)//��������, �� �������� �� ���������� (� � pi)
			{
				p->value=constance(name);//���� ��, �� ������������� ��������
			}
			else
			{
				p->value=ask(name)*sign;//���� ��� - �������� � ����������.
			}

			push(&ints_stack,p->value);//�������� � ����

			if (!q)
			{
				p->next=vars[h];
				vars[h]=p;
			}
			else
			{
				p->next=q->next;
				q->next=p;
			}

			sign=1;
			status=1;

			return;
		}
	}

	if (priority(func(c)))//�������� ���� �������
	{
		switch (c)
		{
			case '(':
				push(&func_stack,c);
				status=2;//����� ������� '-' ����� ���� ������ ������
				return;

			case ')':
				while ((c=pop(&func_stack))!='(')
				{
					counter(&ints_stack,c);//������� ��������� � �������
				}

				if (!empty(func_stack) && priority(top(func_stack)))
				{
					counter(&ints_stack,pop(&func_stack));
				}

				status=1;
				return;

			default:
				if (c=='-' && status==2)
				{
					sign=-1;
					status=2;
					return;
				}

				while (!empty(func_stack) && priority(func(c))<=priority(top(func_stack)))
				{
					counter(&ints_stack,pop(&func_stack));
				}

				push(&func_stack,func(c));

				status=2;
				return;
		}
	}
}
