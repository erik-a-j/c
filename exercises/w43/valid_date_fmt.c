#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define printerr() printf("ERROR at line:%d\n", __LINE__)
// YYYY-MM-DD HH:mm:ss

int main() {
    char *line = NULL;
    size_t len_line = 0;
    size_t size_line = 0;
    getline(&line, &size_line, stdin);

    len_line = strlen(line);

    char *date = line;
    while (isspace(*date)) date++;

    char *p = &line[len_line-1];
    while (*p == '\n' || *p == '\r') {
        *p-- = '\0';
        len_line--;
    }

    printf("entered date: %s\n", date);

    char *date_copy = strdup(date);
    const char *year_str = strtok(date_copy, "-");

    char *endptr;
    long year = strtol(year_str, &endptr, 10);
    if (endptr == year_str || *endptr != '\0') {
        printerr();
        goto End;
    }
    if (year > 7600000000) {
        printf("earth must still exist\n");
        goto End;
    }

    const char *month_str = strtok(NULL, "-");
    long month = strtol(month_str, &endptr, 10);
    if (endptr == month_str || *endptr != '\0') {
        printerr();
        goto End;
    }
    if (month < 1 || month > 12) {
        printf("month must be in range of 01-12\n");
        goto End;
    }

    const char *day_str = strtok(NULL, " ");
    long day = strtol(day_str, &endptr, 10);
    if (endptr == day_str || *endptr != '\0') {
        printerr();
        goto End;
    }
    if (day < 1 || day > 31) {
        printf("day must be in range of 01-31\n");
        goto End;
    }

    const char *hour_str = strtok(NULL, ":");
    long hour = strtol(hour_str, &endptr, 10);
    if (endptr == hour_str || *endptr != '\0') {
        printerr();
        goto End;
    }
    if (hour < 0 || hour > 23) {
        printf("hour must be in range of 00-23\n");
        goto End;
    }

    const char *min_str = strtok(NULL, ":");
    long min = strtol(min_str, &endptr, 10);
    if (endptr == min_str || *endptr != '\0') {
        printerr();
        goto End;
    }
    if (min < 0 || min > 59) {
        printf("min must be in range of 00-59\n");
        goto End;
    }

    const char *sec_str = strtok(NULL, "\0");
    long sec = strtol(sec_str, &endptr, 10);
    if (endptr == sec_str || *endptr != '\0') {
        printerr();
        goto End;
    }
    if (sec < 0 || sec > 59) {
        printf("sec must be in range of 00-59\n");
        goto End;
    }

    printf("Entered date is valid!\n");

End:
    free(date_copy);
    date_copy = NULL;
    free(line);
    line = NULL;
    return 0;
}