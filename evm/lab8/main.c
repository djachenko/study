#include <stdio.h>
#include <time.h>
#include <opencv2/highgui/highgui.hpp>

#define N 300

int main(int argc, char **argv){
    struct timespec start, end, start_wait, end_wait;
	double wait = 0;
	double gclocks = 0;

	struct tms tstart, tend, tstart_wait, tend_wait;
	long clocks_per_sec = sysconf(_SC_CLK_TCK);
	double twait = 0;
	double tclocks = 0;

	CvCapture *capture; //дескриптор обрабатываемого потока данных
	IplImage *frame; //дескриптор растрового изображения
	char c = 0;
	int i = 0;

	if(argc == 1)
		capture = cvCreateCameraCapture(0);
	else
		capture = cvCreateFileCapture(argv[1]);

	times(&tstart);
	clock_gettime(CLOCK_REALTIME, &start);

	while(i < N){

		frame = cvQueryFrame(capture);

		if(!frame)
			break;

		cvShowImage("test2", frame);

		times(&tstart_wait);
        clock_gettime(CLOCK_REALTIME, &start_wait);

		c = cvWaitKey(33);

		clock_gettime(CLOCK_REALTIME, &end_wait);
		times(&tend_wait);

		wait += (double)(end_wait.tv_sec-start_wait.tv_sec + 0.000000001*(end_wait.tv_nsec-start_wait.tv_nsec));
		twait += (double)(tend_wait.tms_utime - tstart_wait.tms_utime);

		if(c == 27)
			break;
		i++;
	}
	clock_gettime(CLOCK_REALTIME, &end);
	times(&tend);

	tclocks = (double)(tend.tms_utime - tstart.tms_utime) / (clocks_per_sec*N);
	gclocks = ((double)(end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec)))/300;

    printf("%lf\n", times_clocks/gettime_clocks);
	printf("%lf\n", times_wait/(wait*clocks_per_sec));

	cvReleaseCapture(&capture);
	cvDestroyWindow("test1");

	return;
}

