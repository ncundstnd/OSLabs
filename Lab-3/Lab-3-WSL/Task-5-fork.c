#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        printf("Child PID: %d-%d\n", getpid(), i);
        sleep(1);
    }

    return 0;
}