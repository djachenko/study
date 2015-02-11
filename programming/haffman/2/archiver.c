#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"
#include "const.h"
#include "types.h"

static void make_codes(struct node * root, struct list * code)
{
	if (root->value!=-1)
	{
		codes[root->value]=list_dup(code);
		return;
	}

	if (root->left)
	{
		list_add(&code,'0');

		make_codes(root->left, code);

		list_tailget(&code);
	}

	if (root->right)
	{
		list_add(&code,'1');

		make_codes(root->right, code);

		list_tailget(&code);
	}
}

static void clear()
{
	int i;

	for (i=0;i<256;i++)
	{
		if (codes[i])
		{
			struct list * p=codes[i];
			struct list * q=NULL;

			while (p)
			{
				q=p;
				p=p->next;
				free(q);
			}
		}
	}
}

static void encoder(FILE * source, FILE * archive)//собственно функция архивации
{
	int c;
	int i;

	fseek(source, 0, SEEK_SET);//сброс курсора в начало файла

	while ((c=fgetc(source))!=EOF)//пока не достигнут конец файла
	{
		list_cat(&buffer,codes[c]);//отправка в буфер кода символа
		buffer_size+=list_len(codes[c]);

		while (buffer_size>=8)//пока буфера хватает на создание байта (если не хватает, вернемся на следующем шаге)
		{
			char symbol_code[9]={0};//массив с кодом результирующего символа

			for (i=0;i<8;i++)
			{
				symbol_code[i]=list_get(&buffer);//выдергивание из буфера по "биту"
			}

			buffer_size-=8;

			int step=1;
			int symbol=0;

			for (i=7;i>=0;i--)//переработка полученного в один символ

			{
				symbol+=step*(symbol_code[i]-'0');
				step*=2;
			}

			fputc(symbol,archive);//его вывод
		}
	}

	char symbol_code[9]={0};

	if (buffer_size)
	{
		for (;buffer_size<8;)
		{
			list_add(&buffer,'0');
			buffer_size++;
		}
	}

	for (i=0;i<8;i++)
	{
		symbol_code[i]=list_get(&buffer);//выдергивание из буфера по "биту"
	}

	buffer_size-=8;

	int step=1;
	int symbol=0;

	for (i=7;i>=0;i--)//переработка полученного в один символ
	{
		symbol+=step*(symbol_code[i]-'0');
		step*=2;
	}

	fputc(symbol,archive);
}

int compare_first (const void * a, const void * b)
{
	  return ( *(int *)b - *(int *)a);
}

int compare (const void * a, const void * b)
{
	  return ( (*(struct node **)b)->freq - (*(struct node **)a)->freq );
}

static struct node * make_tree(FILE * source)
{
	int c;

	struct node * leaves[256];//символы хранятся сразу в листьях

	int i;

	for (i=0;i<256;i++)
		leaves[i]=NULL;

	int n=0;//кол-во различных символов

	while((c=fgetc(source))!=EOF)
	{
		if (!leaves[c])//если такого еще не было
		{
			n++;
			leaves[c]=new_node();
			leaves[c]->value=c;
		}

		leaves[c]->freq++;//увеличить частоту
	}

	if (n==0)
	{
		struct node * root=new_node();

		root->freq=0;

		return root;
	}

	if (n==1)//если один элемент. Ну, тупой такой алгоритм
	{
		int i;

		for (i=0;;i++)//нахождение ТОГО САМОГО элемента
		{
			if (leaves[i])
			{
				break;
			}
		}

		struct node * root=new_node();
		struct node * a=new_node();
		a->value=i;

		root->right=a;//и в дерево его

		return root;
	}
	else//а тут их больше...
	{
		qsort(leaves,256,sizeof(* leaves),compare_first);//нулевые элементы спихиваются в конец

		while (n>1)
		{
			qsort(leaves,n,sizeof(* leaves),compare);//сортировка по частоте

			struct node * a=new_node();//создание связущего узла

			a->left=leaves[n-2];//выдергивание двух узлов
			a->right=leaves[n-1];//с наименьшими частотами
			a->freq=leaves[n-2]->freq+leaves[n-1]->freq;//и суммирование их частот в связку

			leaves[n-2]=a;//замена одного
			leaves[n-1]=NULL;//и вынос другого
			n--;
		}

		return leaves[0];//остался один элемент, его и возвращаем
	}
}

void archivize(char source_name[256], char archive_name[256])
{
	FILE * source=fopen(source_name,"r");

	if (!source)
	{
		printf("Error: source file wasn't opened\n");
		return;
	}

	if (!archive_name[0])
	{
		printf("Enter name of your archive, please: ");
		scanf("%s", archive_name);
	}

	FILE * archive=fopen(archive_name,"w");

	fprintf(archive,"%s ",source_name);

	struct node * root=make_tree(source);

	fprintf(archive,"%d ",root->freq);

	if (root->freq==0)
	{
		cut_tree(root);

		fclose(source);
		fclose(archive);

		return;
	}

	make_codes(root,NULL);

	fprint_tree(root,archive);

	cut_tree(root);

	encoder(source,archive);

	fclose(source);
	fclose(archive);

	clear();
}
