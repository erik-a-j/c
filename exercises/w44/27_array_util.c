#include <stdio.h>

int array_get_max(int arr[], int len) {
    int largest = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > largest) { largest = arr[i]; }
    }
    return largest;
}
int array_get_average(int arr[], int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum / len;
}
int array_find_value(int value, int arr[], int len) {
    for (int i = 0; i < len; i++) {
        if (value == arr[i]) { return i; }
    }
    return -1;
}

int main(void) {
    int arr[5] = {40, 20, 50, 10, 30};

    int largest = array_get_max(arr, 5);
    printf("largest: %d\n", largest);

    int average = array_get_average(arr, 5);
    printf("average: %d\n", average);

    int index = array_find_value(20, arr, 5);
    if (index != -1) {
        printf("found value at arr[%d]: %d\n", index, arr[index]);
    } else {
        printf("no value found\n");
    }

    return 0;
}