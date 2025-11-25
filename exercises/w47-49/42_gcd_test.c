#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include "42_gcd_module.h"

bool charcmp(char a, char b)
{
    if (isupper(a) && islower(b))
    {
        return (a >= (b & ~0x20)) ? true : false;
    }
    else if (isupper(b) && islower(a))
    {
        return (b >= (a & ~0x20)) ? true : false;
    }
    return (a >= b) ? true : false;
}

int main(void)
{
    unsigned int r_gcd = gcd(8, 12);
    assert(r_gcd > 0);
    printf("gcd: %u\n", r_gcd);

    unsigned int r_lcm = lcm(5, 7);
    assert(r_lcm > 0);
    printf("lcm: %u\n", r_lcm);

    char str[] = "ihfwFJIFOaA";
    printf("%s\n", str);
    int r_strsort = strsort(str, charcmp);
    assert(0 == r_strsort);
    printf("%s\n", str);

    return 0;
}