#include <stdio.h>
#include <string.h>

#include "list.h"
#include "tree.h"
#include "const.h"
#include "types.h"

void encode(struct node * root, struct list * code)
{
	if (root->value!=-1)
	{
		printf("(%d)",root);
		print_list(code);
		codes[root->value]=list_dup(code);
		return;
	}

	if (root->left)
	{
		list_add(&code,'0');

		putchar('0');

		encode(root->left, code);

		list_tailget(&code);
	}

	if (root->right)
	{
		list_add(&code,'1');

		putchar('1');

		encode(root->right, code);

		list_tailget(&code);
	}
}

void archiver(FILE * source)//собственно функция архивации
{
	int c;
	int i;

	fseek(source, 0, SEEK_SET);//сброс курсора в начало файла

	while ((c=fgetc(source))!=EOF)//пока не достигнут конец файла
	{
		list_cat(&buffer,codes[c]);//отправка в буфер кода символа
		buffer_size+=list_len(codes[c]);

		while (buffer_size>=8)//пока буфера хватает
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

			putchar(symbol);//его вывод
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

	putchar(symbol);
}

void archivize(char * source_name)
{
	FILE * source=fopen(source_name,"w");

	{
		char c;

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

		struct node * root=new_tree(leaves,n);//создание дерева сообразно частотам

		struct list * code=NULL;

		encode(root,code);//задание кодов символов (массив, каждому символу - список кодов)

		cut_tree(root);
	}

	char archive_name[256]={0};

	printf("Enter name of your archive: ");
	scanf("%s",archive_name);

	freopen(archive_name,"w",stdin);
	printf("%s ",source_name);

	print(root,0);

	putchar(' ');

	archiver(source);

	fclose(source);
}
