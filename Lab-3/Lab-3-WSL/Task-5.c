#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void cycle(int count, char *message)
{
	for (int i = 1; i <= count; i++)
	{
		printf("\n%s %d-%d\n", message, getpid(), i);
		sleep(1);
	}
}

int main()
{
	pid_t child_pid;

	switch (child_pid = fork())
	{
	case -1:
		perror("fork error");
		return -1;
	case 0:
		printf("Fork value returned to the child: %d", child_pid);
		cycle(50, "Child PID:");
		return 0;
	default:
		printf("Fork value returned to the child:%d", child_pid);
		cycle(100, "Parent PID:");
		wait(0);
	}

	return 0;
}