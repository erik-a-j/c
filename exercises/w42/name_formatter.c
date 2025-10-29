#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    bool is_name = false;
    //bool is_first_letter = true;
    char c = '\0';

    while (fscanf(stdin, "%c", &c) == 1) {
        if (!is_name && isspace(c)) continue;
        else if (isspace(c)) {
            //is_first_letter = true;
            is_name = false;
            printf("%c", c);
            continue;
        }
        if (!isalpha(c)) continue;

        if (!is_name) {
            printf("%c", toupper(c));
            is_name = true;
        } else {
            printf("%c", tolower(c));
        }
    }
    printf("\n");
    return 0;
}