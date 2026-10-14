#include <stdio.h>//ask
#include <ctype.h>//parser (переменные)
#include <math.h>//константа пи как аркосинус -1
#include <stdlib.h>//создание переменной
#include <string.h>//создание переменной

#include "functions.h"
#include "const.h"
#include "stack.h"
#include "main.h"

double constance(char * a)
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
	struct stream a;

	printf("Input value of variable %s, please: ",name);
	spacescanf(a.s);
	a.index=0;
	a.funcs=NULL;
	a.ints=NULL;

	return calc(&a);
}

void parser(int c, struct stream * stream)
{
	if (isdigit(c))//встречена цифра, то есть началось число
	{
		double num=0;//заводим переменную под число (дробное)

		while (isdigit(c))//пока число не закончилось
		{
			num=num*10+c-'0';//дописываем цифры
			c=sgetc(stream);
		}

		if (c=='.' || c==',')//переход к дробной части
		{
			int dot=10;//множитель
			c=sgetc(stream);

			while (isdigit(c))//то же, что и выше
			{
				num+=(c-'a')*1.0/dot;

				dot*=10;
				c=sgetc(stream);
			}
		}

		num*=sign;

		push(&(stream->ints),num);//кладется в числовой стек
		unsgetc(stream);

		sign=1;
		status=1;

		return;
	}

	if (isalpha(c))//если встречена буква, то есть переменная
	{
		char name[255]={0};
		int i=0;

		while (isalpha(c))//формирование имени переменной
		{
			name[i]=c;
			i++;
			c=sgetc(stream);
		}

		unsgetc(stream);

		if (func((int)name))//проверка, не функция ли это (переменные sin, cos и т.д. не принимаются)
		{
			push(&(stream->funcs),func((int)name));//если да, то отправка в стек функций
			return;
		}

		//проверка успешно пройдена, это не функция

		int h=hash(name);

		struct hashtable *p=vars[h];
		struct hashtable *q=NULL;

		int d=-1;

		while (p && (d=strcmp(p->variable,name))<0)
		{
			q=p;
			p=p->next;
		}

		if (d==0)//переменная уже была (значение уже задано)
		{
			push(&(stream->ints),p->value);
			return;
		}

		if (d>0 || !p)
		{

			p=malloc(sizeof(*p));
			strcpy(p->variable,name);

			if (constance(name)!=0.0)//проверка, не является ли константой (е и pi)
			{
				p->value=constance(name);//если да, то присваивается значение
			}
			else
			{
				p->value=ask(name)*sign;//если нет - вводится с клавиатуры
			}

			push(&(stream->ints),p->value);//отправка в стек

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

	if (priority(func(c)))//встречен знак функции
	{
		switch (c)
		{
			case '(':
				push(&(stream->funcs),c);
				status=2;//после функции '-' может быть только знаком
				return;

			case ')':
				while ((c=pop(&stream->funcs))!='(')
				{
					counter((&stream->ints),c);//считаем выражение в скобках
				}

				if (!empty(stream->funcs) && priority(top(stream->funcs)))
				{
					counter(&(stream->ints),pop(&(stream->funcs)));
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

				while (!empty(stream->funcs) && priority(func(c))<=priority(top(stream->funcs)))
				{
					counter(&(stream->ints),pop(&(stream->funcs)));
				}

				push(&(stream->funcs),func(c));

				status=2;
				return;
		}
	}
}
