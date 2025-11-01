/*
1) Make a function to fill an array of type int with random numbers in the range 0 and 99.
2) Make a function to print an array of type int to the output.
3) Make a function to swap values of two int variables.
4) Make a function to sort an array of type int. The function shall accept a function pointer of type compare_t to compare two values
    typedef bool (*compare_t)(int, int);

void sort_array(int *arr, size_t length, compare_t compare);
    a) When you sort the array, the compare function shall be used to compare the elements
    b) To swap the elements, the swap function of step 3 shall be used.
    c) Implement two functions, compare_asc and compare_desc, to sort the array ascending and descending

bool compare_asc(int a, int b); and bool compare_desc(int a, int b);
    d) You shall be able to sort the array ascending and descending by calling sort_array with different compare functions

* To handle the arrays use only pointers
*/
#include <stdbool.h>
#include <stdio.h>

static int fill_arr(int *arr, size_t len) {
    FILE *urand = fopen("/dev/urandom", "rb");
    if (!urand) {
        return -1;
    }
    size_t nread = fread(arr, sizeof(int), len, urand);
    if (nread != len) {
        fclose(urand);
        return nread;
    }
    for (int *p = arr; (size_t)(p - arr) < len; p++) {
        *p = ((*p % 100) + 100) % 100;
    }
    return nread;
}

static void print_arr(int *arr, size_t len) {
    for (int *p = arr; (size_t)(p - arr) < len; p++) {
        printf("arr[%ld]: %d\n", (p - arr), *p);
    }
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

typedef bool (*compare_t)(int, int);

bool compare_asc(int a, int b) {
    return a > b;
}
bool compare_desc(int a, int b) {
    return a < b;
}

void sort_array(int *arr, size_t len, compare_t compare) {
    for (int *iptr = arr; (size_t)(iptr - arr) < len; iptr++) {
        for (int *jptr = iptr + 1; (size_t)(jptr - arr) < len; jptr++) {
            if (compare(*iptr, *jptr)) {
                swap(iptr, jptr);
            }
        }
    }
}

int main(void) {
    int arr[10];
    if (fill_arr(arr, 10) != 10) {
        return 1;
    }
    print_arr(arr, 10);
    puts("");
    sort_array(arr, 10, compare_desc);
    print_arr(arr, 10);
    return 0;
}