#include <stdio.h>
#include <stdint.h>


void print_bits(int v) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (v >> i) & 1);
        if (i % 4 == 0) printf(" ");
    }
}

int main() {
    int32_t x = -1;
    uint32_t z = 32;
    double d;

    int32_t a = x / z;
    d = x / z;

    print_bits(a);
    printf("\n");
    printf("%d\n", a);
    printf("%u\n", UINT32_MAX);
    printf("%u\n", (uint32_t)x);
    //printf("%f\n", d);
}