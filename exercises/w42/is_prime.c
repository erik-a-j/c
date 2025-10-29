#include <stdio.h>

typedef unsigned int uint;

int main() {
    int num = 0;
    int r = 0;
    
    printf("enter num 2-10000: ");
    r = scanf("%d", &num);
    while (r != 1 || (num < 2 || num > 10000)) {
        getchar();
        printf("try again: ");
        r = scanf("%d", &num);
    }

    int is_prime = 1;
    for (int i = num-1; i >= 2; i--) {
        if (num % i == 0) {
            is_prime = 0;
            break;
        }
    }
    printf("%d %s a prime number\n", num, (is_prime == 1)? "is" : "is not");
}