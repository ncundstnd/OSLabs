#include <stdio.h>
#include <time.h>

int main() {
    time_t currentTime = time(NULL);

    struct tm *localTime = localtime(&currentTime);

    printf("Текущая локальная дата и время: %02d.%02d.%04d %02d:%02d:%02d\n",
           localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900,
           localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

    return 0;
}