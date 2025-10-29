#include <stdio.h>

static int numlen(int num) {
    int a = num;
    if (num < 0) {
        a = -num;
    }
    if (a < 10) {
        return 1;
    }
    return 1 + numlen(a / 10);
}

static float power(int base, int exp) {
    printf("power(%d, %d) called\n", base, exp);
    int temp = exp;
    if (exp < 0) {
        temp = -exp;
    }
    float result = 1;
    if (temp != 0) {
        result = (base * power(base, temp - 1));
    }
    printf("result == %g\n", result);
    if (exp < 0) {
        return (1 / result);
    }
    return result;
}

#define pnumlen(num) printf(#num " len: %d\n", numlen(num))
#define ppower(x, y) printf(#x "^" #y " == %g\n", power(x, y))
int main(void) {
    ppower(7, 5);
    return 0;
}