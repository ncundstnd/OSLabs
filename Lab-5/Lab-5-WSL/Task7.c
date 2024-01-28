#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid;
    child_pid = fork();

    if (child_pid < 0)
    {
        perror("Ошибка при создании дочернего процесса");
        exit(1);
    }

    if (child_pid == 0)
    {
        nice(10);

        while (1)
        {
            sleep(1);
        }
    }
    else
    {
        printf("Дочерний процесс создан с PID: %d\n", child_pid);

        wait(NULL);
    }

    return 0;
}
