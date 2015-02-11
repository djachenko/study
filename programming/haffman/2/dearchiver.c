#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "list.h"
#include "const.h"

static int size=0;

static void to_bin(int a, int d)//vypisyvanie celoy
{
	if (d==0)
		return;

    	to_bin(a/2,d-1);

	list_add(&buffer,a%2);
	buffer_size++;

    	return;
}

static void decoder(struct node * root, FILE * dest)
{
	if (root->value!=-1)
	{
		fputc(root->value,dest);

		size--;
		return;
	}

	int c=list_get(&buffer);
	buffer_size--;

	switch (c)
	{
		case 0:
			decoder(root->left,dest);
			return;
		case 1:
			decoder(root->right,dest);
			return;
	}
}

void dearchivize(char source_name[256], char dest_name[256])
{
	FILE * source=fopen(source_name,"r");

	if (!source)
	{
		printf("Error: source file wasn't opened\n");
		return;
	}

	char name[256]={0};

	fscanf(source,"%s",name);//чтение имени заархивированного файла
		
	if (!dest_name[0])
	{
		printf("Enter name of dearchivized file (if you want to use default name \"%s\", leave this line empty: ", name);

		int c;
		int i=0;

		while ((c=getchar())!='\n')
		{
			dest_name[i]=c;
			i++;
		}
	}

	if (dest_name[0])
	{
		strcpy(name,dest_name);
	}

	fscanf(source,"%d",&size);//размер

	if (size==0)
	{
		fclose(source);
		FILE * dest=fopen(name,"w");
		fclose(dest);

		return;
	}

	struct node * root=fread_tree(source);//чтение дерева

	int height=tree_height(root);

	FILE * dest=fopen(dest_name,"w");

	while (size)
	{
		while (list_len(buffer)<height)
		{
			to_bin(fgetc(source),8);
		}

		decoder(root,dest);
	}

	list_clear(&buffer);

	cut_tree(root);

	fclose(source);
	fclose(dest);
}
