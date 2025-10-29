#include <stdio.h>

int streq(const char *str1, const char *str2) {
    if (!str1 || !str2) { return 0; }
    const char *p1 = str1;
    const char *p2 = str2;

    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 != *p2) { return 0; }
        p1++;
        p2++;
    }
    return *p1 == '\0' && *p2 == '\0';
}

int main(void) {
    const char *str1 = "string";
    const char *str2 = "string";

    int eq = streq(str1, str2);
    printf("%s %s %s\n", str1, eq ? "==" : "!=", str2);

    return 0;
}