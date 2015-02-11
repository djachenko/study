#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

struct list
{
	double value;
	struct list *next;
};

struct hashtable
{
	char variable[255];
	double value;
	struct hashtable * next;
};

char s[255];

void push(struct list **stack, double a)
{
	struct list *p=malloc(sizeof(*p));

	p->value=a;
	p->next=*stack;

	*stack=p;
}

double d_pop(struct list **stack)
{
	double k=(*stack)->value;
	struct list *p=*stack;

	*stack=(*stack)->next;

	free(p);

	return k;
}

int pop(struct list **stack)
{
	int k=(*stack)->value;
	struct list *p=*stack;

	*stack=(*stack)->next;

	free(p);

	return k;
}

double top(struct list *stack)
{
	return stack->value;
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

	(char *)a;

	if (strcmp(a,"log")==0)
		return 5;
	if (strcmp(a,"sin")==0)
		return 6;
	if (strcmp(a,"cos")==0)
		return 7;
	if (strcmp(a,"sqrt")==0)
		return 8;
	if (strcmp(a,"abs")==0)
		return 9;

	return 0;
}

void counter(struct list **stack, int c)
{
	double a=d_pop(stack);
	double b;

	if (c<=4)
		b=d_pop(stack);

	printf("count %.2lf %.2lf (%d) ",a,b,c);

	switch (c)
	{
		case 1:
			printf("1 %lf\n",b+a);
			push(stack,b+a);
			printf("done %.2lf\n",top(*stack));
			break;
		case 2:
			printf("2 %lf\n",b-a);
			push(stack,b-a);
			break;
		case 3:
			printf("3 %lf\n",b*a);
			push(stack,b*a);
			break;
		case 4:
			printf("4 %lf\n",b/a);
			push(stack,b/a);
			break;
		case 5:
			printf("5 %lf\n",log(a));
			push(stack,log(a));
			break;
		case 6:
			printf("6 %lf\n",sin(a));
			push(stack,sin(a));
			break;
		case 7:
			printf("7 %lf\n",cos(a));
			push(stack,cos(a));
			break;
		case 8:
			printf("8 %lf\n",sqrt(a));
			push(stack,sqrt(a));
			break;
		case 9:
			printf("9 %lf\n",fabs(a));
			push(stack,fabs(a));
			break;

	}

	printf("ed\n");

	return;
}

int hash(char * src)
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

double ask(char * name)
{
	double a;

	printf("Input value of variable %s, please: ",name);
	scanf("%lf",&a);

	return a;
}

int sgetc()
{
	static int index;
	int c;

	c=s[index];

	index++;

	return c;
}

double constance(char * a)
{
	if (strcmp(a,"pi")==0)
		return acos(-1);

	return 357;
}

int main()
{
	struct list * func_stack=NULL;
	struct list * ints_stack=NULL;
	struct hashtable * vars[255];

	int i;

	scanf("%s",s);

	int c=sgetc();

	for (i=0;i<255;i++)
		vars[i]=NULL;

	int sign=1;
	int status=2;

	while (1)
	{
		printf("%c %d\n",c,status);

		if (c==';')
			break;

		//continue;
		if (isdigit(c))//встречена цифра, то есть началось число
		{
			double num=0;//заводим переменную под число (дробное)

			while (isdigit(c))//пока число не закончилось
			{
				num=num*10+c-'0';//дописываем цифры
				c=sgetc();
			}

			if (c=='.' || c==',')//переход к дробной части
			{
				int dot=10;//множитель
				c=sgetc();

				while (isdigit(c))//то же, что и выше
				{
					num+=(c-'a')*1.0/dot;

					dot*=10;
					c=sgetc();
				}
			}

			num*=sign;

			push(&ints_stack,num);//кладется в числовой стек

			sign=1;
			status=1;

			continue;
		}

		if (isalpha(c))//если встречена буква, то есть переменная
		{
			char name[255]={0};
			i=0;

			while (isalpha(c))
			{
				name[i]=c;
				i++;
				c=sgetc();
			}

			if (func(name))
			{
				printf("alpha %d\n",func(name));
				push(&func_stack,func(name));
//				break;
				continue;
			}

			int h=hash(name);

			struct hashtable *p=vars[h];
			struct hashtable *q=NULL;

			int d;

			while (p && (d=strcmp(p->variable,name))<0)
			{
				q=p;
				p=p->next;
			}

			printf("d %d %d ",d,h);

			if (!p)
			{
				printf("p %d\n",p);
			}
			else
			{
				printf("v %s\n",p->variable);
			}

			if (d==0)
			{
				push(&ints_stack,p->value);
				printf("pushed\n");
				continue;
			}

			if (d>0 || !p)
			{
				printf("entered\n");
				p=malloc(sizeof(*p));
				printf("! %s %d\n",name,p->variable);
				strcpy(p->variable,name);

				printf("const\n");

				if (constance(name)!=357.0)
				{
					p->value=constance(name);
				}
				else
				{
					p->value=ask(name)*sign;
				}

				printf("prepush\n");
				push(&ints_stack,p->value);
				printf("pushed\n");


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

				continue;
			}
		}

		int d;

		if (d=encode(c))//встречен знак функции
		{
			switch (c)
			{
				case '(':
					push(&func_stack,c);
					status=2;
					break;

				case ')':
					while ((c=pop(&func_stack))!='(')
					{
						counter(&ints_stack,c);
					}

					if (!empty(func_stack) && encode(top(func_stack)))
					{
						counter(&ints_stack,pop(&func_stack));
					}

					status=1;
					break;

				default:
					if (c=='-' && status==2)
					{
						sign=-1;
						status=2;
						break;
					}

					while (!empty(func_stack) && d<=encode(top(func_stack)))
					{
						counter(&ints_stack,pop(&func_stack));
					}

					push(&func_stack,func(c));

					status=2;
					break;
			}
		}

		c=sgetc();
	}

	printf("pp\n");

	while (func_stack)
	{
		//printf("%d ",func_stack);
		counter(&ints_stack,pop(&func_stack));
		//printf("%lf\n",d_pop(&ints_stack));
		printf("fs %.2lf\n",top(ints_stack));
		printf("fe\n");
	}

	//printf("%c\n",pop(&func_stack));
	printf("%.2lf\n",top(ints_stack));

	return 0;
}
