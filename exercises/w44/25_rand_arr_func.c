#include <stdio.h>

int unique_rand_array(int arr[], int len) {
    FILE *urand = fopen("/dev/urandom", "rb");
    if (!urand) { return -1; }

    if (fread(arr, sizeof(int), len, urand) != (size_t)len) {
        fclose(urand);
        return -1;
    }
    for (int i = 0; i < len; i++) {
        arr[i] = ((arr[i] % 99) + 99) % 99 + 1;
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len;) {
            if (i == j) {
                j++;
                continue;
            }
            if (arr[i] == arr[j]) {
                printf("detected simularity: arr[%d]: %d, arr[%d]: %d\n", i, arr[i], j, arr[j]);
                if (fread(&arr[i], sizeof(int), 1, urand) != 1) {
                    fclose(urand);
                    return -1;
                }
                arr[i] = ((arr[i] % 99) + 99) % 99 + 1;
                j = 0;
                continue;
            }
            j++;
        }
    }

    fclose(urand);
    return 0;
}

void print_array(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("array[%d]: %d\n", i, arr[i]);
    }
}

int main(void) {
    int arr[10];
    const int arr_len = sizeof(arr) / sizeof(arr[0]);
    if (unique_rand_array(arr, arr_len) != 0) { return 1; }

    print_array(arr, arr_len);

    return 0;
}