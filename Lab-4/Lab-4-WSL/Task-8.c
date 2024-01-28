#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *threadFunction(void *arg)
{
    for (int i = 1; i <= 75; i++)
    {
        (i == 50) ? sleep(10) : 0;
		printf("AdditionalThread\tPID: %d\t", getpid());
		printf("TID: %li\t%d\n", syscall(SYS_gettid), i);
		sleep(1);
    }
    return NULL;
}

int main()
{

    pthread_t thread;

    int result = pthread_create(&thread, NULL, threadFunction, NULL);

    for (int i = 1; i <= 100; i++)
    {
        (i == 30) ? sleep(15) : 0;
		printf("MainThread\t\tPID: %d\t", getpid());
		printf("TID: %li\t%d\n", syscall(SYS_gettid), i);
		sleep(1);
    }

    pthread_join(thread, NULL);

    return 0;
}