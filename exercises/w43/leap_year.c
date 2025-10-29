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
    int is_leap_year = 0;
    size_t len_year_str = strlen(year_str);
    if (year_str[len_year_str-1] == '0' && year_str[len_year_str-2] == '0') {
        is_leap_year = (year % 400 == 0)? 1 : 0;
    } else {
        is_leap_year = (year % 4 == 0)? 1 : 0;
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

    int max_days[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    const char *day_str = strtok(NULL, " ");
    long day = strtol(day_str, &endptr, 10);
    if (endptr == day_str || *endptr != '\0') {
        printerr();
        goto End;
    }
    if (day > max_days[month-1]) {
        if (!is_leap_year) {
            printf("invalid day of month\n");
            goto End;
        } else if (month != 2 || day != 29) {
            printf("invalid day of month\n");
            goto End;
        }
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