#ifndef types_h
#define types_h

struct list
{
	int value;
	struct list * next;
};

struct queue
{
	struct list * head;
	struct list * tail;
};

struct node
{
	int value;
	struct node * left;
	struct node * right;
};

#endif // types_h
