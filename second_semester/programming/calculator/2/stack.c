#include <stdlib.h>

#include "types.h"

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
