#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

int main()
{
	struct list *stack=NULL;
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
					push(&stack,source[i]);
					break;

				case ')':
					while ((c=pop(&stack))!='(')
					{
						polish[used]='!';
						polish[used+1]=c;
						used+=2;
					}

					if (!empty(stack) && encode(top(&stack)))
					{
						polish[used]='!';
						polish[used+1]=pop(&stack);
						used+=2;
					}

					break;

				default:
					while (!empty(stack) && d<=encode(top(&stack)))
					{
						polish[used]='!';
						polish[used+1]=pop(&stack);
						used+=2;
					}

					push(&stack,source[i]);
					break;
			}

			i++;
		}
	}

	while (stack)
	{
		polish[used]='!';
		polish[used+1]=pop(&stack);
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
