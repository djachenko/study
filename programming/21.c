#include <stdio.h>
#include <stdlib.h>

struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
};

void print(struct tree *p)
{
	if (p->left) print(p->left);

	printf("%d ",p->data);

	if (p->right) print(p->right);
}

void mem(struct tree *p)
{
	if (!p) return;

	mem(p->left);
	mem(p->right);

	free(p);

	return;
}

int main()
{
	struct tree *root=NULL;

	FILE *f=fopen("21.txt","r");

	int a;

	if (fscanf(f,"%d",&a)==1) 
	{
		struct tree *p=malloc(sizeof(struct tree));
		p->data=a;
		p->left=NULL;
		p->right=NULL;
		root=p;
	}
	else 
	{
		printf("empty file\n");
		return(0);
	}

	while(fscanf(f,"%d",&a)==1)
	{
	//	printf("1 %d\n",a);

		struct tree *p=root;
		struct tree *q=NULL;

		while(p)
		{
			q=p;

			if (p->data<a) p=p->left;
			else p=p->right;
		}

		p=malloc(sizeof(struct tree));

		p->data=a;
		p->left=NULL;
		p->right=NULL;

		if(q)
		{
			if (q->data<a) q->left=p;
			else q->right=p;
		}
	}

	print(root);

	putchar('\n');

	mem(root);

	return(0);
}
