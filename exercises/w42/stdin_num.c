#include <stdio.h>

int main() {
    int num = 0;
    fscanf(stdin, "%d", &num);

    if (num < 0) {
        printf("num: %d is not a positive number\n", num);
        return 1;
    }

    printf("num: %d\n", num);

    int sum = 0;
    for (int i = 0; i <= num/2; i++) {
        sum += i * 2;
    }

    printf("sum: %d\n", sum);
    return 0;
}