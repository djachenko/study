#include <stdio.h>

#define MAX 10000

char mem[MAX];

void *myalloc(size_t size)
{
	int *sum=(int *)mem;

	if (!*sum) *sum=0;

	int *flag=(int *)mem+sizeof(int)+*mem;

	*flag=size;

	*sum+=(size+sizeof(int));

	return(flag+1);
}

void myfree(void *p)
{
	int *sum=(int *)mem;

	char *q=(char *)p+*(int *)(p-sizeof(int));

	p-=sizeof(int);

	*sum-=(*(int *)p+sizeof(int));

	int k=*(int *)q+sizeof(*(int *)q);

	*(int *)mem-=*(int *)q;

	int i;

	for (i=0;i<k;i++)
	{
		 *((char *)p+i)=*((char *)q+i);
	}

	return;
}

void check()
{
	if (*(int *)mem)
		printf("WARNING! ");

	printf("You have %d allocated bytes.\n",*(int *)mem);
}

int main()
{
	int i;

	int *b=myalloc(3*sizeof(int));

	int *c=myalloc(5*sizeof(int));

	for (i=0;i<5;i++)
		c[i]=i+1;

	myfree(b);

	int *d=myalloc(2*sizeof(int));

	for (i=0;i<2;i++)
		d[i]=9;

	myfree(c);

	myfree(d);

	check();

	return 0;
}
