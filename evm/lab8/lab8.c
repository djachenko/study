#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
	CvCapture *capture;
	IplImage *frame;

	char c;

	cvNamedWindow("test2",CV_WINDOW_AUTOSIZE);

	if(argc == 1)
	{
		capture = cvCreateCameraCapture(0);
	}
	else
	{
		capture = cvCreateFileCapture(argv[1]);
	}

	struct timespec gettime_start;
	struct timespec gettime_end;

	struct tms times_start;
	struct tms times_end;

	clock_gettime(CLOCK_REALTIME, &gettime_start);
	times(&times_start);

	int i;

	for (i=0; i<1024; i++)
	{
		frame = cvQueryFrame(capture);

		if(!frame)
		{
			break;
		}

		cvShowImage("test2", frame);

		c = cvWaitKey(33);


		if(c == 27)
		{
			break;
		}

		printf("%d\n",i);
	}
	
	clock_gettime(CLOCK_REALTIME, &gettime_end);
	times(&times_end);

	cvReleaseCapture(&capture);

	cvDestroyWindow("test2");

	printf("gettime: %lf\n", gettime_end.tv_sec - gettime_start.tv_sec + 0.000000001 * ( gettime_end.tv_nsec - gettime_start.tv_nsec));

	printf("Time taken: %lf sec.\n", (double)(times_end.tms_utime - times_start.tms_utime) / sysconf(_SC_CLK_TCK));

	

	return 0;
}
