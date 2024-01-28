#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sched.h>

int main()
{
    pid_t process_id = getpid();
    pid_t thread_id = syscall(SYS_gettid);

    for (int i = 0; i < 100000; i++)
    {
        sleep(1);
    }

    return 0;
}
