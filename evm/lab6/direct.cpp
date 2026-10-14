#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv)
{
	for (int i=1; i<=1024; i++)
	{
		int size=i*1024/sizeof(int);

		int * arr=new int[size];

		memset(arr,0,sizeof(int));

		switch(argv[1][0])
		{
			case 'd':
				for (int j=0; j<size-1; j++)
				{
					arr[j]=j+1;
				}

				arr[size-1]=0;

				break;
			case 'b':
				for (int j=1; j<size; j++)
				{
					arr[j]=j-1;
				}

				arr[0]=size-1;
					
				break;

			case 'r':
				for (int j=0; j<size; j++)
				{
					arr[j]=j;
				}

				srand(time(NULL));
			
				for (int j=size-1; j>=0; j--)
				{
					int r=rand()%(j+1);

					int b=arr[j];
					arr[j]=arr[r];
					arr[r]=b;
				}
		}

		for (int j=arr[0]; j!=0; )
		{
			j=arr[j];
		}

	
		double min=500000;

		for (int k=0; k<3; k++)
		{
		
			struct timespec start;
			struct timespec end;
	
			clock_gettime(CLOCK_REALTIME, &start);

			for (int j=arr[0]; j!=0; )
			{
				j=arr[j];
			}

			clock_gettime(CLOCK_REALTIME, &end);
		
			if (end.tv_sec-start.tv_sec+ 0.000000001*(end.tv_nsec-start.tv_nsec)<min)
			{
				min=end.tv_sec-start.tv_sec+ 0.000000001*(end.tv_nsec-start.tv_nsec);
			}
		}

		printf("%d	%lf\n",i,min);
	}

	return 0;
}
