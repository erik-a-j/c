#include <stdio.h>

typedef struct {
    int age;
    float height;
    char name[16];
} person_t;

person_t get_person() {
    person_t person = {0};

    printf("Enter age: ");
    if (scanf("%d", &person.age) != 1) { return person; }
    printf("Enter height: ");
    if (scanf("%f", &person.height) != 1) { return person; }
    printf("Enter name: ");
    if (scanf("%s", person.name) != 1) { return person; }

    return person;
}

int main(void) {
    person_t person = get_person();

    printf(".age: %d\n", person.age);
    printf(".height: %.2f\n", person.height);
    printf(".name: %s\n", person.name);

    return 0;
}