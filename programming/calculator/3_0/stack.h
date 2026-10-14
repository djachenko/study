#include "types.h"

#ifndef stack_h
#define stack_h

void push(struct list **stack, double a);
double d_pop(struct list **stack);
int pop(struct list **stack);
double top(struct list *stack);
int empty(struct list *stack);

#endif
