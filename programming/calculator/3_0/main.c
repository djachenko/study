#include <stdio.h>

#include "stack.h"
#include "types.h"
#include "functions.h"
#include "counter.h"
#include "parser.h"

struct list * func_stack=NULL;//stack of codes of functions
struct list * ints_stack=NULL;//stack of operands

char s[255];//source of non-parsed sentence

int sign=1;//number which defines sign of operand
int status=2;//number which defines if this '-' is operation or sign

struct hashtable * vars[255];//hashtable of variables

double calc()
{
	int c;

	while (1)//разбор выражения
	{
		c=sgetc();

		if (c==0)
			break;

		parser(c);
	}

	while (func_stack)
	{
			counter(&ints_stack,pop(&func_stack));
	}

	return ints_stack->value;
}


int main()
{
	scanf("%s",s);
	int c;

	int i;

	for (i=0;i<255;i++)
		vars[i]=NULL;

	while(1)
	{
		reset();

		printf("%lf\n",calc());

		if (!check())
		{
			clear();
			break;
		}

		clear();
	}


	return 0;
}
