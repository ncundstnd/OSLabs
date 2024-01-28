#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

pthread_mutex_t mutex;
pthread_mutex_t console_mutex;
int shared_iteration = 1;

void *threadFunction(void *arg)
{
    char thread_name = *((char *)arg);
    pid_t thread_id = syscall(SYS_gettid);

    for (int i = 1; i <= 90; ++i)
    {
        if (i == 30)
        {
            pthread_mutex_lock(&mutex);
        }
        if (i == 60)
        {
            pthread_mutex_unlock(&mutex);
        }

        pthread_mutex_lock(&console_mutex);
        std::cout << i << ' ' << thread_name << " id = " << thread_id << std::endl;
        pthread_mutex_unlock(&console_mutex);

        usleep(100000); // Задержка в 0.1 секунды
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t threadA, threadB;

    pthread_mutex_init(&mutex, NULL);

    char threadA_name = 'A';
    char threadB_name = 'B';

    if (pthread_create(&threadA, NULL, threadFunction, (void *)&threadA_name) != 0 ||
        pthread_create(&threadB, NULL, threadFunction, (void *)&threadB_name) != 0)
    {
        std::cerr << "Error creating threads" << std::endl;
        return 1;
    }

    pid_t main_thread_id = syscall(SYS_gettid);

    for (int i = 1; i <= 90; ++i)
    {
        if (i == 30)
        {
            pthread_mutex_lock(&mutex);
        }
        if (i == 60)
        {
            pthread_mutex_unlock(&mutex);
        }

        pthread_mutex_lock(&console_mutex);
        std::cout << i << " M id = " << main_thread_id << std::endl;
        pthread_mutex_unlock(&console_mutex);

        usleep(100000); // Задержка в 0.1 секунды
    }

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
