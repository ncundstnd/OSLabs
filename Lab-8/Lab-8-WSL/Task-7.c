#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    size_t size = 256 * 1024 * 1024;
    int *intArray = (int *)malloc(size);

    for (size_t i = 0; i < size / sizeof(int); ++i) {
        intArray[i] = i + 1;
    }
    printf("Address : %p\n", (void *)intArray);
    printf("%d\n", getpid());

    sleep(300); 

    free(intArray);

    return 0;
}
