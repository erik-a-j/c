#include <assert.h>
#include <stdio.h>
#include "42_module.h"

int main(void)
{
    unsigned int r_gcd = gcd(8, 12);
    assert(r_gcd > 0);
    printf("gcd: %u\n", r_gcd);

    unsigned int r_lcm = lcm(5, 7);
    assert(r_lcm > 0);
    printf("lcm: %u\n", r_lcm);

    char str[] = "ihfwFJIFOaA";
    int r_strsort = strsort(str);

    return 0;
}