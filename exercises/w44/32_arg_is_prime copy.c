#include <stdio.h>

#define isint(ch) ((ch) >= 48 && (ch) <= 57)
#define toint(ch) (ch) - 48

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("missing arg\n");
        return 1;
    }
    char *p = argv[1];
    if (*p == '-') {
        printf("must be positive int\n");
        return 1;
    }

    int num = 0;
    while (*p != '\0') {
        if (!isint(*p)) {
            printf("must be int\n");
            return 1;
        }
        num *= 10;
        num += toint(*p);
        p++;
    }

    int is_prime = 1;
    for (int i = num - 1; i >= 2; i--) {
        if (num % i == 0) {
            is_prime = 0;
            break;
        }
    }

    printf("%d is %s prime\n", num, is_prime ? "a" : "not a");

    return 0;
}