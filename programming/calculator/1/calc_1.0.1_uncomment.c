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

int func(int a)
{
	switch (a)
	{
		case '(':
			return -2;
		case ')':
			return -1;
		case '+':
			return 1;
		case '-':
			return 2;
		case '*':
			return 3;
		case '/':
			return 4;
		case '^':
			return 5;
	}


	if (strcmp((char *)a,"log")==0)
		return 6;
	if (strcmp((char *)a,"sin")==0)
		return 7;
	if (strcmp((char *)a,"cos")==0)
		return 8;
	if (strcmp((char *)a,"sqrt")==0)
		return 9;
	if (strcmp((char *)a,"abs")==0)
		return 10;

	return 0;
}

void counter(struct list **stack, int c)
{
	double a=d_pop(stack);
	double b;

	if (c<=5)
		b=d_pop(stack);

	switch (c)
	{
		case 1:
			push(stack,b+a);
			break;
		case 2:
			push(stack,b-a);
			break;
		case 3:
			push(stack,b*a);
			break;
		case 4:
			push(stack,b/a);
			break;
		case 5:
			push(stack,pow(b,a));
			break;
		case 6:
			push(stack,log(a));
			break;
		case 7:
			push(stack,sin(a));
			break;
		case 8:
			push(stack,cos(a));
			break;
		case 9:
			push(stack,sqrt(a));
			break;
		case 10:
			push(stack,fabs(a));
			break;
	}

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
	if (strcmp(a,"e")==0)
		return 2.71828;

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
		if (c==';')
			break;

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

			if (func((int)name))
			{
				push(&func_stack,func((int)name));
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

			if (d==0)
			{
				push(&ints_stack,p->value);
				continue;
			}

			if (d>0 || !p)
			{

				p=malloc(sizeof(*p));
				strcpy(p->variable,name);

				if (constance(name)!=357.0)
				{
					p->value=constance(name);
				}
				else
				{
					p->value=ask(name)*sign;
				}

				push(&ints_stack,p->value);

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

		if (d=encode(func(c)))//встречен знак функции
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

	while (func_stack)
	{
		counter(&ints_stack,pop(&func_stack));
	}

	printf("%.2lf\n",top(ints_stack));

	return 0;
}
//было 453
