#include "types.h"
#include <stdio.h>

#ifndef const_h
#define	const_h

extern int sign;//number which defines sign of operand
extern int state;//�������� ������� ��� �������. ���������� ������ ��� ���������� �������� �� main
extern int errorcode;
extern FILE * logfile;//���-����

extern struct hashtable * vars[255];//hashtable of variables

#endif
