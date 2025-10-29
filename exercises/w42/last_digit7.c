#include <stdio.h>


int main() {
    int num = 1000;

    while (num >= 7) {
        if (num % 10 == 7) {
            printf("%d\n", num);            
        }
        num--;
    }
    return 0;
}