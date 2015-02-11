#include "types.h"
#include <stdio.h>

#ifndef const_h
#define	const_h

extern int sign;//number which defines sign of operand
extern int state;//конечный автомат для парсера. глобальный потому что приходится задавать из main
extern int errorcode;
extern FILE * logfile;//лог-файл

extern struct hashtable * vars[255];//hashtable of variables

#endif
