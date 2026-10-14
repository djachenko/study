#include <stdio.h>

#include "list.h"
#include "types.h"

int main()
{
	int a;

	struct list * test=NULL;

	for (a=7;a;)
	{
		scanf("%d",&a);
		list_add(&test,a);
		print_list(test);
	}

	return 0;
}
