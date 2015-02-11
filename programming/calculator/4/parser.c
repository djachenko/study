#include <ctype.h>//parser (переменные)
#include <math.h>//константа пи как аркосинус -1
#include <stdlib.h>//создание переменной
#include <string.h>//создание переменной

#include "functions.h"
#include "const.h"
#include "stack.h"
#include "main.h"
#include "counter.h"

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
	if (c==5 || c==11)
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

static double sg(int c)
{
	if (c<0)
		return -1;
	if (c>0)
		return 1;
	
	return 0; 
}

void parser_right(int c, struct stream * stream)
{
	if (isdigit(c))//встречена цифра, то есть началось число
	{
		if (state%2!=0)//проверка на предыдущие состояния
		{
			errorcode=6;
			return;
		}

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

			if (!isdigit(c))
			{
				errorcode=6;
				return;
			}

			while (isdigit(c))//то же, что и выше
			{
				num+=(c-'0')*1.0/dot;

				dot*=10;
				c=sgetc(stream);
			}

			if (!(c==')' || c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='=' || c==0))
			{
				errorcode=6;
				return;
			}
		}
		unsgetc(stream);

		num*=sign;

		push(&(stream->ints),num);//кладется в числовой стек

		sign=1;
		state=3;
		return;
	}

	if (isalpha(c))//если встречена буква, то есть переменная или функция с текстоым представлением
	{
		if (state%2!=0)
		{
			errorcode=6;
			return;
		}

		char name[255]={0};
		int i=0;

		while (isalnum(c))//формирование имени переменной
		{
			name[i]=c;
			i++;
			c=sgetc(stream);
		}

		unsgetc(stream);

		if (func((int)name))//проверка, не функция ли это (переменные sin, cos и т.д. не принимаются)
		{

			int c=sgetc(stream);

			if (c=='(' || isdigit(c))
			{
				unsgetc(stream);
				push(&(stream->funcs),func((int)name));//если да, то отправка в стек функций
			}
			else
			{
				errorcode=6;
				return;
			}

			state=6;//отметка об одноместности функции?
			return;
		}

		//проверка успешно пройдена, это не функция

		int h=hash(name);

		struct hashtable * p=vars[h];


		int d=-1;

		while (p && (d=strcmp(p->variable,name))<0)
		{
			p=p->next;
		}

		if (d==0)//переменная уже была (значение уже задано)
		{
			push(&(stream->ints),p->value);
		}
		else//переменной не было, задать ее
		{
			if (constance(name)!=0.0)//проверка, не является ли константой (е и pi)
			{
				push(&(stream->ints),constance(name));//если да, то кладется значение
			}
			else
			{
				push(&(stream->ints),0);//если нет - 0
			}
		}

		state=3;//переменность
		return;
	}

	if (func(c))//встречен знак функции
	{
		switch (c)
		{
			case '(':
				if (state%2!=0)
				{
					errorcode=7;
					return;
				}
				
				push(&(stream->funcs),c*sign);
				state=0;//после скобки хоть потоп
				sign=1;
				return;

			case ')':
				if (state%3!=0 || state==0)
				{
					errorcode=7;
					return;
				}

				while ((c=pop(&stream->funcs))!='(' && c!=-1*'(')
				{
					counter((&stream->ints),c);//считаем выражение в скобках
				}

				push(&(stream->ints),d_pop(&(stream->ints))*sg(c));

				if (!empty(stream->funcs) && priority(top(stream->funcs)))
				{
					counter(&(stream->ints),pop(&(stream->funcs)));
				}

				state=3;
				return;

			default:
				if (c=='-' && (state%2==0))
				{
					sign*=-1;
					state=6;
					return;
				}

				if (state%3!=0 || state==0)
				{
					errorcode=6;
					return;
				}

				while (!empty(stream->funcs) && priority(func(c))<=priority(top(stream->funcs)))
				{
					counter(&(stream->ints),pop(&(stream->funcs)));
				}

				push(&(stream->funcs),func(c));

				state=2;
				return;
		}
	}

	errorcode=6;
	return;
}

struct hashtable * parser_left(char * name)
{
	int h=hash(name);

	struct hashtable *p=vars[h];
	struct hashtable *q=NULL;

	int d=-1;

	while (p && (d=strcmp(p->variable,name))<0)//поиск
	{
		q=p;
		p=p->next;
	}

	if (d>0 || !p)//переменной не было, задать ее
	{
		p=malloc(sizeof(*p));
		strcpy(p->variable,name);

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
	}

	return p;
}
