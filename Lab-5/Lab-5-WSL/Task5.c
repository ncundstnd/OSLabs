#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sched.h>

int main()
{
    pid_t process_id = getpid();
    pid_t thread_id = syscall(SYS_gettid);

    for (int i = 0; i < 1000; i++)
    {
        printf("Process ID:\t %d\n", process_id);
        printf("Thread ID:\t %d\n", thread_id);
        printf("Thread nice:\t %d\n", getpriority(PRIO_PROCESS, thread_id));
        sleep(1);
    }

    return 0;
}
