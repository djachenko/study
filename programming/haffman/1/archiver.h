#ifndef archiver_h
#define archiver_h

#include "types.h"

void archiver(FILE * source, struct node * root);//���������� ������� ���������
void archivize(FILE * source, char * source_name, struct node * root);

#endif
