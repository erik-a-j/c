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

    printf("line: %s\n", line);


    char *token = strtok(line, " ");
    if (token) {
        printf("%s\n", token);
    }
    while ((token = strtok(NULL, " ")) != NULL) {
        printf("%s\n", token);
    }

    free(line);
    line = NULL;
    
    return 0;
}
