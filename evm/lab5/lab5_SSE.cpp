#include <iostream>
#include <fstream>
#include <sys/times.h>
#include <unistd.h>

#include "SSEMatrix.h"

#include "size.h"

int main()
{
	ifstream input;

	input.open("lab5.txt");

	SSEMatrix A(size, size);

	input >> A;

	input.close();

	struct tms start;
	struct tms end;
	struct tms loopStart;
	struct tms loopEnd;

	long clocksPerSec = sysconf(_SC_CLK_TCK);

	times(&start);

	SSEMatrix result(size, size);

	SSEMatrix r = E( A.height() );
	SSEMatrix matR = R(A);
	SSEMatrix matB = B(A);
//start

	times(&loopStart);

	for (int i = 0; i < 10; i++)
	{
		result += r;

		r *= matR;
	}

	times(&loopEnd);

	result *= matB;
//finish

	times(&end);

	double loop = (double)(loopEnd.tms_utime - loopStart.tms_utime) / clocksPerSec;
	double whole = (double)(end.tms_utime - start.tms_utime) / clocksPerSec;

	cout << loop/N << '	' << whole - loop << '	' << whole << endl;

	return 0;
}
