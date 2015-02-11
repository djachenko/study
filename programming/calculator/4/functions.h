#include "types.h"

#ifndef functions_h
#define functions_h

int sgetc(struct stream * a);
void unsgetc(struct stream * a);
void reset(struct stream * a);
int func(int a);
int check();//проверка: если все переменные 0 - 0, если есть !0 - 2, если пусто - 1
void clear_stream(struct stream * stream);//очистка потока
void clear_hashtable(void);//очистка таблицы переменных
void spacescanf(char * s);

#endif
