#include <math.h>

#include "stack.h"
#include "types.h"

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
		case 11:
			push(stack,a*a);
			break;
	}

	return;
}
