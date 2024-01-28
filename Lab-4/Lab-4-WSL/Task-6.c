#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main()
{
	for (int i = 1; i <= 100; i++)
	{
		printf("PID: %d\t", getpid());
		printf("TID: %li\t%d\n", syscall(SYS_gettid), i);
		sleep(1);
	}

	return 0;
}