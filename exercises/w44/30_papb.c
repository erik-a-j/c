#include <stdio.h>

void add_five(int *a) {
    if (a) { *a += 5; }
}

void say_value(int a) {
    printf("Value of a is %d\n", a);
}
typedef void (*say_value_t)(int a);

int main(void) {
    int a = 5;
    char b = 's';

    int *pa = &a;
    char *pb = &b;

    *pa = 10;
    *pb = 'z';

    add_five(&a);

    say_value_t say = say_value;
    say(a);

    printf("%c\n", b);
}