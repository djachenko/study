#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

#define N 50000 

int main()
{
	int a[N]={0};

	struct timespec gettime_start;
	struct timespec gettime_end;

	struct tms times_start;
	struct tms times_end;
	long clocks_per_sec = sysconf(_SC_CLK_TCK);
	long clocks;

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

	clock_gettime(CLOCK_REALTIME, &gettime_start);
	times(&times_start);
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

	clock_gettime(CLOCK_REALTIME, &gettime_end);
	times(&times_end);
	asm("rdtsc\n": "=a" (rdtsc_end.t32.th), "=d" (rdtsc_end.t32.tl));

	clocks=times_end.tms_utime-times_start.tms_utime;

	printf("clock_gettime: %lf\n", gettime_end.tv_sec - gettime_start.tv_sec + 0.000000001 * ( gettime_end.tv_nsec - gettime_start.tv_nsec ) );
	printf("times: %lf\n", (double)clocks/clocks_per_sec);
	printf("rtdsc: %lf\n", (rdtsc_end.t64-rdtsc_start.t64)/cpu_Hz);
	
	return 0;
}