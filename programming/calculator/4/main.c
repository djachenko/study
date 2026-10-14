#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"//pop в calc
#include "types.h"
#include "functions.h"//sgetc
#include "counter.h"
#include "parser.h"
#include "error.h"

int sign=1;//number which defines sign of operand
int errorcode=0;//код ошибки
int state=0;//для конечного автомата в парсере, но яхз, как его объявлять там.
FILE * logfile;//лог-файл

struct hashtable * vars[255];//hashtable of variables

double calc(struct stream * stream)//запуск подсчета.
{
	if (strcmp(stream->s,"")==0)//проверка на пустое выражение
	{
		errorcode=5;
		return 0;
	}

	{//проверка скобок
		int i;
		int l=strlen(stream->s);
		int k=0;

		for (i=0;i<l;i++)
		{
			if (stream->s[i]=='(')
				k++;
			if (stream->s[i]==')')
				k--;

			if (k<0)
			{
				break;
			}
		}

		if (k!=0)
		{
			errorcode=6;
			return 0;
		}
	}//проверка скобок

	if (strchr(stream->s,'='))
	{
		errorcode=6;
		return 0;
	}

	int c;
	state=0;//входное состояние
	sign=1;

	while (!errorcode)//разбор выражения
	{
		c=sgetc(stream);

		if (c==0)
			break;

		parser_right(c,stream);
	}

	if (errorcode)
		return 0;

	if (state%3!=0)
	{
		errorcode=7;
		return 0;
	}

	while (stream->funcs)//досчитывает то, что не в скобках (скобки разобраны парсером)
	{
		counter(&(stream->ints),pop(&(stream->funcs)));
	}

	return d_pop(&(stream->ints));
}

int main()
{
	int i;

	for (i=0;i<255;i++)
		vars[i]=NULL;

	logfile=fopen("log.txt","a");
	fprintf(logfile,"start\n");

	while(1)
	{
		char s[256]={0};
		errorcode=0;//начинаем без ошибок

		printf("> ");

		spacescanf(s);//чтение очередной строки

        fprintf(logfile,"> %s\n",s);

		if (strcmp(s,"")==0)//проверка на пустой ввод
		{
			errorcode=1;
			error();
			continue;
		}

		struct stream mainstream;//source of non-parsed sentence. Приходится городить эту хрень здесь, ибо что-то в clear подать таки надо

		mainstream.index=0;
		mainstream.ints=NULL;
		mainstream.funcs=NULL;

		//код ошибки ноль
		if (strcmp(s,"stop")==0 || strcmp(s,"stopit")==0)//условие остановки
		{
			clear_stream(&mainstream);//очистка потока
			clear_hashtable();//очистка таблицы переменных
			fclose(logfile);
			return 0;
		}

		char * is=strchr(s,'=');//нахождение знака равенства (если нет - NULL)

		if (!is)//равно нет, просто посчитать
		{
			strcpy(mainstream.s,s);//отправляем всю строку в поток

			double answer=calc(&mainstream);

			if (!errorcode)
			{
				printf("%lf\n",answer);//вывод результата
				fprintf(logfile,"< %lf\n",answer);//вывод результата в лог
			}
		}
		else//придется это запоминать
		{
			int l=is-s;//длина левой части
			char name[256]={0};//место под имя переменной

			strncpy(name,s,l);//копирование левой части в "имя"

			for (i=0;i<l;i++)//проверка имени на наличие знаков
			{
				if (!isalpha(name[i]) && !isdigit(name[i]))
				{
					errorcode=2;//чтоб за один цикл выйти
					break;
				}
			}

			if (errorcode || func((int)name) || constance(name)!=0.0)//если есть либо знак, либо функция, либо константа
			{
				errorcode=2;
			}//все ок, хорошее имя

			if (!errorcode)//если так ничего и не произошло
			{
				strcpy(mainstream.s,is+1);//правую часть (выражение) в поток

				double answer=calc(&mainstream);//посчитать и запомнить

				if (!errorcode)
				{
					printf("%lf\n",answer);//вывод результата
					fprintf(logfile,"< %lf\n",answer);
					parser_left(name)->value=answer;//и хренакс значение выражения в переменную
				}
			}
		}

		clear_stream(&mainstream);

		error();//подытоживание
	}

	fclose(logfile);

	return 0;
}
