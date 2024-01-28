#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define BILLION 1000000000L

int main()
{
	struct timespec start_real_time, end_real_time, proc;
	clock_t start_cpu_time, end_cpu_time;
	int iteration_counter = 0;

	clock_gettime(CLOCK_REALTIME, &start_real_time);
	start_cpu_time = clock();

	while (1)
	{
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc);
		iteration_counter++;
		if (proc.tv_sec == 2)
		{
			clock_gettime(CLOCK_REALTIME, &end_real_time);
			end_cpu_time = clock();
			break;
		}
	}

	long real_time_elapsed = (end_real_time.tv_sec - start_real_time.tv_sec) * BILLION +
							 (end_real_time.tv_nsec - start_real_time.tv_nsec);

	printf("Iteration: %d, Time spended: %ld nanoseconds.\n", iteration_counter, real_time_elapsed);

	return 0;
}