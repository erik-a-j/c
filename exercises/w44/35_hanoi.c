/*
Read about the hanoi tower puzzle and solve it for 64 disks. https://romek.info/games/hanoi3e.html

Make a program to find the number of years it takes to move 64 disks from a peg to another peg if each move takes 1 second.
*/

#include <stdint.h>
#include <stdio.h>

#define DISKS           64U
#define SECONDS_IN_YEAR (365 * 24 * 60 * 60)

static float hanoi(uint8_t n) {
    if (n == 1) {
        return 1.0f;
    }
    return 2 * hanoi(n - 1) + 1.0f;
}

int main(void) {
    float years = hanoi(DISKS) / SECONDS_IN_YEAR;
    (void)printf("it takes %g years to move %u disks\n", years, DISKS);
    return 0;
}