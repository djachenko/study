#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "list.h"
#include "const.h"

void encode(struct node * root, struct list * code)
{
	if (root->value!=-1)
	{
		printf("(%d)",root);
		print_list(code);
		codes[root->value]=list_dup(code);
		//codes[root->value]=code;
		return;
	}

	if (root->left)
	{
		list_add(&code,'0');

		putchar('0');
		
		encode(root->left, code);

		list_tailget(&code);
	}

	if (root->right)
	{
		list_add(&code,'1');

		putchar('1');

		encode(root->right, code);

		list_tailget(&code);
	}
}
