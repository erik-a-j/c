#include <stdio.h>

int numlen(int num) {
    int a = (num < 0) ? -num : num;
    return (a < 10) ? 1 : (1 + numlen(a / 10));
}

static float power(int base, int exp) {
    int temp = (exp < 0) ? -exp : exp;
    float result = (temp == 0) ? 1 : (base * power(base, temp - 1));
    return (exp < 0) ? (1 / result) : result;
}

#define pnumlen(num) printf(#num " len: %d\n", numlen(num))
int main(void) {
    printf("5 ^ 3 == %.2f\n", power(5, 3));
    return 0;
}