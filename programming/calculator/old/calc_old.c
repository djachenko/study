#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct list
{
	int value;
	struct list *next;
};

void push(struct list **stack, int a)
{
	struct list *p=malloc(sizeof(*p));

	p->value=a;
	p->next=*stack;

	*stack=p;
}

int pop(struct list **stack)
{
	int k=(*stack)->value;
	struct list *p=*stack;

	*stack=(*stack)->next;

	free(p);

	return k;
}

int top(struct list **stack)
{
	return (*stack)->value;
}

int empty(struct list *stack)
{
	if (stack)
		return 0;

	return 1;
}

int encode(int c)
{
	switch (c)
	{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
		case '(':
			return -1;
		case ')':
			return -1;
	}

	return 0;
}

void counter(void)
{
	if (isdigit(c))
	{
		double num=0;

		while (isdigit(c))
		{
			num=num*10+c-'0';
			i++;
			c=getchar();
		}

		if (c=='.' || c==',')
		{
			int dot=10;
			c=getchar();

			while (isdigit(c))
			{
				num+=(c-'a')*1.0/dot;

				dot*=10;
				c=getchar();
			}
		}

		push(&func_stack,num);

		continue;
	}

	if (func(c))
	{
		double a=pop(&func_stack);
		double b=pop(&func_stack);

		switch (func(c))
		{
			case 1:
				push(&func_stack,b+a);
				break;
			case 2:
				push(&func_stack,b-a);
				break;
			case 3:
				push(&func_stack,b*a);
				break;
			case 4:
				push(&func_stack,b/a);
				break;
		}

		continue;
	}
}

int main()
{
	struct list * func_stack=NULL;
	struct list * ints_stack=NULL;
	int c;

	char *source=NULL;

	int chunk=10;
	int used=0;
	int size=0;

	while ((c=getchar())!='.')
	{
		if (size<=used)
		{
			char *p=realloc(source,size+chunk);

			source=p;
			size+=chunk;
		}

		source[used]=c;
		used++;
	}
	source[used]=0;

	char *polish=malloc(used*2);
	used=0;

	int vars[255]={0};
	int n=0;

	int i=0;

	while (1)
	{
		if (!source[i])
			break;

		if (isdigit(source[i]))
		{
			polish[used]='|';
			used++;

			while (isdigit(source[i]))
			{
				polish[used]=source[i];
				used++;

				i++;
			}

			continue;
		}

		if (isalpha(source[i]))
		{
			vars[ source[i] ]=1;

			polish[used]='&';
			polish[used+1]=source[i];
			used+=2;

			i++;
			n++;

			continue;
		}

		int d;

		if (d=encode(source[i]))
		{
			switch (source[i])
			{
				case '(':
					push(&func_stack,source[i]);
					break;

				case ')':
					while ((c=pop(&func_stack))!='(')
					{
						polish[used]='!';
						polish[used+1]=c;
						used+=2;
					}

					if (!empty(func_stack) && encode(top(&func_stack)))
					{
						polish[used]='!';
						polish[used+1]=pop(&func_stack);
						used+=2;
					}

					break;

				default:
					while (!empty(func_stack) && d<=encode(top(&func_stack)))
					{
						polish[used]='!';
						polish[used+1]=pop(&func_stack);
						used+=2;
					}

					push(&func_stack,source[i]);
					break;
			}

			i++;
		}
	}

	while (func_stack)
	{
		polish[used]='!';
		polish[used+1]=pop(&func_stack);
		used+=2;
	}

	for (i=0;i<used;i++)
		putchar(polish[i]);

	if (n)
	{
		printf("\nInput variables, please\n");

		for (i=0;i<255;i++)
			if (vars[i])
			{
				printf("%c = ",i);
				scanf("%d",&vars[i]);
			}

		for (i=0;i<used;i++)
		{
			if (polish[i]=='&')
			{
				i++;
				printf("|%d",vars[polish[i]]);
			}
			else
				putchar(polish[i]);
		}
	}


	return 0;
}
