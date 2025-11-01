#include <stdio.h>

/*
1) Make a function to fill an array of type int with random numbers.
2) Make a function to print an array of type int to the output.
3) Make a function to print a 2D array of type int to the output.
* To handle the arrays use only pointers
*/

size_t fill_arr(int *arr, size_t len) {
    FILE *urand = fopen("/dev/urandom", "rb");
    if (!urand) {
        return -1;
    }
    fread(arr, sizeof(int), len, urand);
    fclose(urand);
    return len;
}

void print_arr(const int *arr, size_t len) {
    for (const int *p = arr; p < (arr + len); p++) {
        printf("arr[%d]: %d\n", (int)(p - arr), *p);
    }
}

void print_2darr(const int (*arr)[], size_t rows, size_t cols) {
    int (*matrix)[cols] = (int (*)[cols])arr;
    for (int (*rptr)[cols] = matrix; (size_t)(rptr - matrix) < rows; rptr++) {
        printf("arr[%ld]: {", (rptr - matrix));
        for (int *cptr = *rptr; (size_t)(cptr - *rptr) < cols; cptr++) {
            printf("[%ld] = %d, ", (cptr - *rptr), *cptr);
        }
        printf("}\n");
    }
}

int main(void) {
    int arr[10];
    if (fill_arr(arr, 10) != 10) {
        return 1;
    }
    print_arr(arr, 10);
    int arr2d[3][5] = {
        {10, 20, 100, 400, 32},
        {30, 40, 200, 432, 56},
        {30, 40, 200, 123, 65},
    };
    print_2darr(arr2d, 3, 5);
    return 0;
}