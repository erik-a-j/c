/*
Write a program to make an array of person_t dynamically.

The program shall ask the user to enter length of the array.
Then the program shall allocate memory for the array.
Then the program shall ask the user to enter name and age of each person.
Memory for the name member shall be allocated dynamically.
Then the program shall print all the persons to the output.
In the end the program shall release all the dynamically allocated memory.
*/
#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    uint8_t age;
} person_t;

void free_all_persons(person_t **persons, size_t n)
{
    for (person_t *p = *persons; p < (*persons + n); p++)
    {
        free(p->name);
    }
    free(*persons);
    *persons = NULL;
}

int main(void)
{
    person_t *persons = NULL;
    size_t npersons = 0;
    (void)printf("Hur många mähän ska det vara? ");
    if (1 != scanf("%lu", &npersons) || npersons == 0)
    {
        (void)fprintf(stderr, "FEL!\n");
        return 1;
    }
    (void)getchar();
    (void)printf("antal: %lu\n", npersons);

    persons = malloc(npersons * sizeof(person_t));

    int exit_code = 0;
    for (size_t i = 0; i < npersons; i++)
    {
        size_t name_size = 0;
        char *name = NULL;
        (void)printf("Vad heter mähä nr%d? ", (int)i + 1);
        if (-1 == getline(&name, &name_size, stdin))
        {
            (void)fprintf(stderr, "FEL!\n");
            exit_code = 1;
            break;
        }
        size_t name_len = strlen(name);
        for (char *p = name + name_len - 1; p >= name; p--)
        {
            if (('\n' != *p) && (' ' != *p))
            {
                break;
            }
            *p = '\0';
        }
        if ('\0' == name[0])
        {
            free(name);
            i--;
            continue;
        }

        uint8_t age = 0;
        (void)printf("hur gammal är %s? ", name);
        if (1 != scanf("%hhu", &age))
        {
            (void)fprintf(stderr, "FEL!\n");
            exit_code = 1;
            break;
        }
        (void)getchar();

        persons[i].name = name;
        persons[i].age = age;
    }
    if (0 == exit_code)
    {
        (void)printf(" --- alla mähäs ---\n");
        for (person_t *p = persons; p < (persons + npersons); p++)
        {
            (void)printf("mähä nr%d: namn: %s, ålder: %hhu\n", (int)(p - persons) + 1, p->name, p->age);
        }
    }

    free_all_persons(&persons, npersons);
    return 0;
}