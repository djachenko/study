#ifndef types_h
#define types_h

struct list
{
	double value;
	struct list * next;
};

struct stream
{
	char s[255];
	int index; 
};

struct hashtable
{
	char variable[255];
	double value;
	struct stream stream;
	struct hashtable * next;
};

#endif
