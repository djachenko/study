#include "types.h"

#ifndef functions_h
#define functions_h

int sgetc(struct stream * a);
void unsgetc(struct stream * a);
void reset(struct stream * a);
int func(int a);
int check();//��������: ���� ��� ���������� 0 - 0, ���� ���� !0 - 2, ���� ����� - 1
void clear();//������� ������� ����������
void spacescanf(char * s);

#endif
