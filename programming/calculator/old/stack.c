#include <stdlib.h>

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
