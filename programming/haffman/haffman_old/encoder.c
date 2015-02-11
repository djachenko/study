#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "list.h"

struct list * codes[257];//коды символов. хранятся списками
int code_lens[257];//длины кодов символов
static struct list * buffer;//буфер
static int buffer_size;//размер буфера

void to_buffer(int c)//отправка в буфера кода символа
{
	listcat(buffer,listdup(codes[c]));
	buffer_size+=code_lens[c];//прибавление размера
}

void print_code(void)//вывод куска буфера в итоговый файл (если буфера хватит на символ)
{
	if (buffer_size<8)//на символ не хватит
	{
		return;
	}

	int i=8;
	int c=0;

	while (i)//перевод в двоичную систему
	{
		c=c*2+buffer->value;

		struct list * p=buffer;
		buffer=buffer->next;
		free(p);
	}

	putchar(c);//вывод
}

void encoder(struct node * a, struct list * code)//задание кодов символов из дерева (code - описание пути до ноды от корня)
{
	if (!a)//в жопу ушли
	{
		return;
	}

	if (a->value!=-1)//о, символ!
	{
		codes[a->value]=code;//можно просто присвоить и не чистить
		code_lens=listlen(code);//длина кода символа
		return;
	}

	struct list * b=new_list();

	b->value=0;//код ребра
	encoder(a->left,listcat(code,b));//прифигачиваем этот код к уже имеющемуся коду

	b->value=1;
	encoder(a->left,listcat(code,b));

	return;
}

void archiver(char * source_name, char * archive_name)//процедура архивации (откуда и куда)
{
	FILE * source=fopen(source_name,"r");//исходник
	freopen(archive_name,"w",stdout);//итоговый файл

	printf("%s ",source_name);//вывод названия, чтоб потом восстановить
	print(root);//вывод дерева скобочной записью
	putchar(' ');//разделитель

	buffer_size=0;//очевидно, как Ландау

	int c;

	while (1)
	{
		c=fgetc(source);//прочитали...

		to_buffer(c);//...вбуфернули...

		print_code();//...и попробовали писать
	}
}
