#include <stdio.h>
#include <time.h>

int main()
{
	FILE * direct=fopen("direct.txt","w");
	FILE * reverse=fopen("reverse.txt","w");
	FILE * random=fopen("random.txt","w");

	for (int i=1; i<=1024; i++)
	{
		int size=i*1024/sizeof(int);

		int arr[size]={0};

		for (int j=0; j<size-1; i++)
		{
			arr[j]=j+1;
		}

		arr[size]=0;

		for (int j=arr[0]; j!=0; )
		{
			j=arr[j];
		}

		struct timespec start;
		struct timespec end;

		clock_gettime(CLOCK_REALTIME, &start);

		for (int j=arr[0]; j!=0; )
		{
			j=arr[j];
		}

		clock_gettime(CLOCK_REALTIME, &end);

		fprintf(direct,"%d %lf",i,end.tv_sec-start.tv_sec+ 0.000000001*(end.tv_nsec-start.tv_nsec));

		for (int j=0; j<size; j++)
		{
			arr[j]=size-j-1;
		}

		for (int j=arr[0]; j!=0; )
		{
			j=arr[j];
		}

	}

	fclose(direct);
	fclose(reverse);
	fclose(random);

	return 0;
}
