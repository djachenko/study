#include <stdio.h>

#define N 50000 

int main()
{
	int a[N]={0};

	union ticks
	{   
		unsigned long long t64;

		struct s32
		{
			long th;
			long tl; 
		}t32;

	} rdtsc_start, rdtsc_end;
	double cpu_Hz=3000000000ULL;

	int i;
	int j;

	for (i=0;i<N;i++)
	{
		a[i]=getchar();
	}

	asm("rdtsc\n": "=a" (rdtsc_start.t32.th), "=d" (rdtsc_start.t32.tl));

	for (i=0;i<N;i++)
	{
		for (j=1;j<N;j++)
		{
			if (a[j]<a[j-1])
			{
				int b=a[j];
				a[j]=a[j-1];
				a[j-1]=b;
			}
		}
	}

	asm("rdtsc\n": "=a" (rdtsc_end.t32.th), "=d" (rdtsc_end.t32.tl));

	printf("%lf\n", (rdtsc_end.t64-rdtsc_start.t64)/cpu_Hz);
	
	return 0;
}
