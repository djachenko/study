#include <stdio.h>

#include "types.h"
#include "tree.h"
#include "encoder.h"
#include "archiver.h"

struct list * codes[256];
struct list * buffer;
int buffer_size=0;

int main(int argc,char *argv[])
{
	FILE * source=fopen("input.txt","r");

	char c;

	struct node * leaves[256];//символы хранятся сразу в листьях

	int i;

	for (i=0;i<256;i++)
		leaves[i]=NULL;

	int n=0;//кол-во различных символов

	while((c=fgetc(source))!='\n')
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

	archivize(source,"input.txt",root);

	fclose(source);

	return(0);
}
