#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("\nParent PID: %d\n", getpid());
	int rVal = system("./Task5F");
	printf("rVal value: %d", rVal);
	for (int i = 1; i <= 100; i++)
	{
		printf("\nParent PID: %d-%d", getpid(), i);
		sleep(1);
	}

	return 0;
}
