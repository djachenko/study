#ifndef types_h
#define types_h

struct list
{
	double value;
	struct list * next;
};

struct stream
{
	char s[256];
	int index;
	struct list * funcs;//stack of codes of functions
	struct list * ints;//stack of operands
};

struct hashtable
{
	char variable[255];
	double value;
	struct hashtable * next;
};

#endif
