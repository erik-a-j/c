#include <stdio.h>

int main(void) {
    int disks = 64;
    size_t moves = (1UL << disks) - 1;
    double years = (double)moves / 60.0 / 60.0 / 24.0 / 365.0;
    printf("disks: %d, moves: %lu, year: %lf\n", disks, moves, years);
    return 0;
}