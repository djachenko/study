#include "ScheduledExecutor.h"
#include <iostream>

int main(int argc, char* argv[]) {
	ScheduledExecutor executor(1);

	auto start = steady_clock::now();

	executor.ScheduleDelayedTask([start]{ cout << "task " << duration_cast<duration<double>>(steady_clock::now() - start).count() << endl; }, milliseconds(3000));
	this_thread::sleep_for(seconds(1));
		

	cout << "main " << duration_cast<duration<double>>(steady_clock::now() - start).count() << endl;

	this_thread::sleep_for(seconds(5));
}
