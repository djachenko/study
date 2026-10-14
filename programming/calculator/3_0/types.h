#ifndef types_h
#define types_h

struct list
{
	double value;
	struct list * next;
};

struct hashtable
{
	char variable[255];
	double value;
	struct hashtable * next;
};

#endif
