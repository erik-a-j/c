#include <stdio.h>

int main() {
    int arr[3][3] = {0};

    for (int i = 0; i < 3; i++) {
        printf("Enter ',' delimited elements of arr[%d][0,1,2]: ", i);
        scanf("%d%*[^0-9]%d%*[^0-9]%d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }
    for (int i = 0; i < 3; i++) {
        printf("[%d][0]: %d, [%d][1]: %d, [%d][2]: %d\n", i, arr[i][0], i, arr[i][1], i, arr[i][2]);
    }

    return 0;
}