#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("\nParent PID: %d\n", getpid());
    execl("./Task5F", "Task7F", NULL);        

    for (int i = 1; i <= 100; i++)
    {
        printf("Parent PID: %d-%d\n", getpid(), i);
        sleep(1);
    }

    perror("execl");
	return 1;
}
