#include <stdio.h>

void print_bin_repr(int num) {
    int found_msb = 0;
    for (int i = (8 * sizeof(int))-1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (bit == 1) {
            found_msb = 1;
        }
        if (found_msb == 1) {
            printf("%d", bit);
            if (i % 4 == 0) printf(" ");
        }
    }
    printf("\n");
}

int main() {
    unsigned int num = 0;
    int r = 0;
    printf("enter num 0-255: ");
    r = scanf("%u", &num);
    while (num > 255 || r != 1) {
        getchar();
        printf("try again: ");
        r = scanf("%u", &num);
    }
    printf("binary representation of %u: ", num);
    print_bin_repr((int)num);
    return 0;
}