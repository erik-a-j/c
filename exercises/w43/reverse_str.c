#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *line = NULL;
    size_t len_line = 0;
    size_t size_line;
    getline(&line, &size_line, stdin);
    len_line = strlen(line);

    char *p = &line[len_line-1];
    while (*p == '\n' || *p == '\r') {
        *p-- = '\0';
        len_line--;
    }

    printf("size_line: %lu\n", size_line);
    printf("len_line: %lu\n", len_line);
    printf("line: %s\n", line);
    
    printf("reversed line: ");
    while (p >= line) {
        printf("%c", *p--);
    }

    printf("\n");

    free(line);
    line = NULL;
    return 0;
}
