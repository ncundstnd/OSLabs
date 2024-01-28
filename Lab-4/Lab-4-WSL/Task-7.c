#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *threadFunction(void *arg)
{
    for (int i = 1; i <= 75; i++)
    {
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
		printf("MainThread\t\tPID: %d\t", getpid());
		printf("TID: %li\t%d\n", syscall(SYS_gettid), i);
		sleep(1);
    }

    pthread_join(thread, NULL);

    return 0;
}