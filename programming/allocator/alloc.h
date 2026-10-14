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

void mem_check()
{
	if (*(int *)mem)
		printf("WARNING! ");

	printf("You have %d allocated bytes.\n",*(int *)mem);
}
