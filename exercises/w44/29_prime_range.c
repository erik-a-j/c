#include <stdio.h>

typedef unsigned int uint;

void print_primes_range(uint m, uint n) {
    uint low = (m < n) ? m : n;
    uint high = (n > m) ? n : m;

    printf("primes: {");
    for (uint num = low; num <= high; num++) {
        int is_prime = 1;
        for (int i = num - 1; i >= 2; i--) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) { printf("%u, ", num); }
    }
    printf("}\n");
}

int main(void) {
    print_primes_range(1u, 50u);
    return 0;
}