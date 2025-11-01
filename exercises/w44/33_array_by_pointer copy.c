#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fill_array_rand(int *arr, int len) {
    int fd = open("/dev/urandom", O_RDONLY | __O_CLOEXEC);
    if (fd == -1) { return -1; }

    ssize_t nbytes = read(fd, arr, sizeof(int) * len);
    close(fd);
    return (nbytes == (ssize_t)sizeof(int) * len) ? 0 : -1;
}

void print_arr(int *arr, int len) {
    for (int *p = arr; p < (arr + len); p++) {
        printf("array[%d]: %d\n", (int)(p - arr), *p);
    }
}

int main(void) {
    int arr[10];
    if (fill_array_rand(arr, 10) == 0) { print_arr(arr, 10); }
    return 0;
}