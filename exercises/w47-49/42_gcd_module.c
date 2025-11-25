/*
Make a utility module to provide the following functionalities:

    A function to get the greatest common divisor (gcd) of two unsigned integers greater than 0.
        Example: the gcd of 8 and 12 is 4.
    A function to get the least common multiple(lcm) of two unsigned integers greater than 0.
        Example: the lcm of 4 and 6 is 12.
    A function to sort a string in alphabetical order.
        Example:
            String: jsaNSHosAlPWnSJq
            Sorted String: AaHJjlNnoPqSSssW

Make a test program to test the functions using assertion.

How to Find the GCF Using Euclid's Algorithm

    Given two whole numbers where a is greater than b, do the division a ÷ b = c with remainder R.
    Replace a with b, replace b with R and repeat the division.
    Repeat step 2 until R=0.
    When R=0, the divisor, b, in the last equation is the greatest common factor, GCF.

*/
#include "42_gcd_module.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

unsigned int gcd(unsigned int a, unsigned int b)
{
    if (0 == a || 0 == b)
    {
        return 0;
    }
    if (b > a)
    {
        unsigned int tmp = a;
        a = b;
        b = tmp;
    }

    unsigned int result = b;
    unsigned int remainder = b;
    while (remainder > 0)
    {
        remainder = a % b; // 4 //0
        result = b;        // 8 //4
        a = b;             // 12
        b = remainder;     // 4
    }
    return result;
}

unsigned int lcm(unsigned int a, unsigned int b)
{
    unsigned int r_gcd = gcd(a, b);
    return (r_gcd > 0) ? (a * b) / r_gcd : 0;
}

int strsort(char *s, cmp_char_t cmp)
{
    if (NULL == s || NULL == cmp)
    {
        return -1;
    }

    size_t len = strlen(s);
    if (len < 2)
    {
        return 0;
    }

    for (char *iptr = s; (size_t)(iptr - s) < len; iptr++)
    {
        for (char *jptr = iptr + 1; (size_t)(jptr - s) < len; jptr++)
        {
            if (cmp(*iptr, *jptr))
            {
                char tmp = *iptr;
                *iptr = *jptr;
                *jptr = tmp;
            }
        }
    }
    return 0;
}