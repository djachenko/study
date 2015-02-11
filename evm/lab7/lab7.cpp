#include <stdio.h>
#include <cstdlib>
#include <ctime>

int main()
{
	int blockSize=16*1024 / sizeof(int);

	int offset=1024*1024 / sizeof(int);

	for (int N=1; N<=20; N++)
	{
		int * array=new int[offset*N];

		int size=blockSize/N;

		for (int i=0; i<N; i++)
		{
			int k=1;

			for (int j=0; j<size; j++)
			{
				array[i*offset+j]=(i+1)*offset+j;
			}
		}

		for (int j=0; j<size; j++)
		{
			array[(N-1)*offset+j]=j+1;
		}

		array[(N-1)*offset+size-1]=0;

		struct timespec start;
		struct timespec end;

		double min=0;

		for (int i=0; i<3; i++)
		{

			clock_gettime(CLOCK_REALTIME, &start);

			for (int current=array[0]; current!=0; current=array[current])
			{
			}
	
			clock_gettime(CLOCK_REALTIME, &end);

			double time=end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec);

			if (!min || time<min)
			{
				min=time;
			}
		}

		printf("%d %lf\n", N, (min*1000000)/offset/N);

		delete [] array;
	}

	return 0;
}
