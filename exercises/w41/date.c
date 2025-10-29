#include <stdio.h>

typedef struct {
    int day;
    int month;
    int year;
} date_t;

int main() {
    date_t date = {0};

    printf("Enter date: ");
    scanf("%4d%*c%2d%*c%2d", &date.year, &date.month, &date.day);

    printf("date: %d-%d-%d\n", date.year, date.month, date.day);
}
