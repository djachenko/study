#include <stdlib.h>

#include "const.h"
#include "types.h"

void clear()
{
	int i;

	for (i=0;i<256;i++)
	{
		if (codes[i])
		{
			struct list * p=codes[i];
			struct list * q=NULL;

			while (p)
			{
				q=p;
				p=p->next;
				free(q);
			}
		}
	}
}
