#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct list
{
	double value;
	struct list *next;
};

void push(struct list **stack, double a)
{
	struct list *p=malloc(sizeof(*p));

	p->value=a;
	p->next=*stack;

	*stack=p;
}

double pop(struct list **stack)
{
	double k=(*stack)->value;
	struct list *p=*stack;

	*stack=(*stack)->next;

	free(p);

	return k;
}

int func(int a)
{
	switch (a)
	{
		case '+':
			return 1;
		case '-':
			return 2;
		case '*':
			return 3;
		case '/':
			return 4;
	}

	return 0;
}

int main()
{
	int c;

	int i=0;

	struct list * stack=NULL;

	while ((c=getchar() )!='\n')
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

			push(&stack,num);

			continue;
		}

		if (func(c))
		{
			double a=pop(&stack);
			double b=pop(&stack);

			switch (func(c))
			{
				case 1:
					push(&stack,b+a);
					break;
				case 2:
					push(&stack,b-a);
					break;
				case 3:
					push(&stack,b*a);
					break;
				case 4:
					push(&stack,b/a);
					break;
			}

			continue;
		}
	}

	printf("%.2lf\n",pop(&stack));

	return 0;
}
