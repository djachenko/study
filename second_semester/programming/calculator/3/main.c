#include <stdio.h>

#include "stack.h"
#include "types.h"
#include "functions.h"
#include "counter.h"
#include "parser.h"

struct list * func_stack=NULL;//stack of codes of functions
struct list * ints_stack=NULL;//stack of operands

struct stream mainstream;//source of non-parsed sentence

int sign=1;//number which defines sign of operand
int status=2;//number which defines if this '-' is operation or sign

struct hashtable * vars[255];//hashtable of variables

int main()
{
	scanf("%s",mainstream.s);
	mainstream.index=0;

	printf("%s\n",mainstream.s);

	return 0;

	int c;

	int i;

	for (i=0;i<255;i++)
		vars[i]=NULL;
	
	while (1)
	{
		reset(mainstream);

		while (1)
		{
			c=sgetc(mainstream);

			if (c==0)
				break;

			parser(c,mainstream);
		}
	
		int stop=check();
		
		if (stop==0)
			break;
			
		if (stop>=1)
		{
			while (func_stack)
			{
				counter(&ints_stack,pop(&func_stack));
			}	
			
			printf("%.2lf\n",ints_stack->value);

			clear();
		}

		if (stop==1)
			break;
	}

	return 0;
}
