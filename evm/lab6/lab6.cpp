#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv)
{
	int i=atoi(argv[2]);

	{
		int size=i*1024/sizeof(int);

		int * arr=new int[size];

		memset(arr,0,i*1024);

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
				bool * used= new bool[size];

		                for (int i = 0; i <size; i++)
                		{
		                    used[i] = false;
		                }

                		int i = 0;
		                used[0] = true;

				for (int count=0 ; count<size; count++)
				{
					int next = 0;

					for ( ; used[next]; )
					{
						next = rand() % size;
					}

					arr[i] = next;
					used[i] = true;

					i = next;
                		}

                		arr[i] = 0;

				delete[] used;
		}

		for (int j=arr[0]; j!=0; )
		{
			j=arr[j];
		}

		double min=0;

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

			if (!min || end.tv_sec-start.tv_sec+ 0.000000001*(end.tv_nsec-start.tv_nsec)<min)
			{
				min=end.tv_sec-start.tv_sec+ 0.000000001*(end.tv_nsec-start.tv_nsec);
			}
		}

		printf("%d	%lf\n", i, min);

		delete[] arr;
	}

	return 0;
}
