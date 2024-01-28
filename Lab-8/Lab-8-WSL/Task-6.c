#include <stdio.h>
#include <unistd.h>

int main()
{
    while (1)
	{
		printf("PID: %d\t", getpid());
	}

	return 0;
}