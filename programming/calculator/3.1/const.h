#include "types.h"

#ifndef const_h
#define	const_h

extern struct list * func_stack;//stack of codes of functions
extern struct list * ints_stack;//stack of operands

extern char s[255];//source of non-parsed sentence

extern int sign;//number which defines sign of operand
extern int status;//number which defines if this '-' is operation or sign

extern struct hashtable * vars[255];//hashtable of variables

#endif
