#include <stdlib.h>

#include "types.h"
#include "list.h"

void queue_cat(queue * to, queue * from)
{
	queue_add_list(to, from->head);
}

void queue_add_list(queue * to, list * from)
{
	to->tail->next=list_dup(from);
	
	while (to->tail->next)
	{
		to->tail=to->tail->next;
	}
}
