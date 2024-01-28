#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sched.h>

int main()
{
    pid_t process_id = getpid();
    pid_t thread_id = syscall(SYS_gettid);
    int nice_value = getpriority(PRIO_PROCESS, thread_id);

    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    sched_getaffinity(0, sizeof(cpu_set), &cpu_set);

    printf("Process ID:\t %d\n", process_id);
    printf("Thread ID:\t %d\n", thread_id);
    printf("Thread nice:\t %d\n", nice_value);
    printf("Processors:\t ");
    for (int i = 0; i < CPU_SETSIZE; i++)
    {
        if (CPU_ISSET(i, &cpu_set))
        {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
