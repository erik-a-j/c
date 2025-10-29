#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *line = NULL;
    size_t len_line = 0;
    size_t size_line = 0;
    getline(&line, &size_line, stdin);

    len_line = strlen(line);

    char *p = &line[len_line-1];
    while (*p == '\n' || *p == '\r') {
        *p-- = '\0';
        len_line--;
    }

    p = line;
    while (*p != '\0') {
        if (*p >= 65 && *p <= 90) {
            *p += 32;
        } else if (*p >= 97 && *p <= 122) {
            *p -= 32;
        }
        p++;
    }

    printf("caseswap: %s\n", line);

    free(line);
    line = NULL;
    return 0;
}