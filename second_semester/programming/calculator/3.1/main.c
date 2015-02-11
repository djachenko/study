#include <stdio.h>

#include "stack.h"
#include "types.h"
#include "functions.h"
#include "counter.h"
#include "parser.h"

/*
struct list * func_stack=NULL;//stack of codes of functions
struct list * ints_stack=NULL;//stack of operands
*/

int sign=1;//number which defines sign of operand
int status=2;//number which defines if this '-' is operation or sign

struct hashtable * vars[255];//hashtable of variables

double calc(struct stream * stream)
{
	int c;

	while (1)//разбор выражения
	{
		c=sgetc(stream);

		if (c==0)
			break;

		parser(c,stream);
	}

	while (stream->funcs)
	{
			counter(&(stream->ints),pop(&(stream->funcs)));
	}

	return stream->ints->value;
}

int main()
{
	struct stream mainstream;//source of non-parsed sentence

	spacescanf(mainstream.s);

	mainstream.index=0;
	mainstream.ints=NULL;
	mainstream.funcs=NULL;

	int i;

	for (i=0;i<255;i++)
		vars[i]=NULL;

	while(1)
	{
		reset(&mainstream);

		printf("%lf\n",calc(&mainstream));

		if (!check())
		{
			clear(&mainstream);
			break;
		}

		clear();
	}


	return 0;
}
