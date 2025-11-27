#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define DB_FILE_NAME "student.b"
#define NAME_LEN     32
typedef struct {
    int id;
    int age;
    char name[NAME_LEN + 1];
} student_t;

static int createStudent(int id)
{
    FILE *db = fopen(DB_FILE_NAME, "ab");
    if (NULL == db)
    {
        printf("Error creating student!\n");
        return -1;
    }

    student_t student = {.id = id};

    printf("Enter Age: ");
    while ((scanf("%d", &student.age)) != 1 || (student.age < 5 || student.age > 75))
    {
        getchar();
        printf("Enter age: ");
    }
    getchar();
    printf("Enter Name: ");
    fgets(student.name, NAME_LEN + 1, stdin);
    for (int i = NAME_LEN; i >= 0; i--)
    {
        if (student.name[i] != '\0' && student.name[i] != '\n')
        {
            break;
        }
        student.name[i] = '\0';
    }

    if (1 != fwrite(&student, sizeof(student_t), 1, db))
    {
        printf("Error creating student!\n");
        fclose(db);
        return -1;
    }
    printf("Student created\n");

    fclose(db);
    return 0;
}

void printMenu(void)
{
    printf("===== Student DB =====\n");
    printf("A) Print All Students\n");
    printf("C) Create A Student\n");
    printf("P) Print A Student\n");
    printf("E) Edit A Student\n");
    printf("Q) Quit\n");
}

static int getGreatestId(void)
{
    FILE *db = fopen(DB_FILE_NAME, "rb");
    if (NULL == db)
    {
        printf("Error reading id!\n");
        return -1;
    }
    if (0 != fseek(db, 0, SEEK_END))
    {
        printf("Error seeking!\n");
        return -1;
    }

    long db_size = ftell(db);
    if (0 != fseek(db, 0, SEEK_SET))
    {
        printf("Error seeking!\n");
        return -1;
    }

    int greatest_id = 0;
    while (db_size > 0)
    {
        student_t student = {0};
        if (1 != fread(&student, sizeof(student_t), 1, db))
        {
            printf("Error reading id!\n");
            return -1;
        }
        if (student.id > greatest_id)
        {
            greatest_id = student.id;
        }
        db_size -= sizeof(student_t);
    }

    fclose(db);
    return greatest_id;
}

static int printAllStudents(void)
{
    FILE *db = fopen(DB_FILE_NAME, "rb");
    if (NULL == db)
    {
        printf("Error printing all students!\n");
        return -1;
    }
    if (0 != fseek(db, 0, SEEK_END))
    {
        printf("Error seeking!\n");
        return -1;
    }

    long db_size = ftell(db);
    if (0 != fseek(db, 0, SEEK_SET))
    {
        printf("Error seeking!\n");
        return -1;
    }
    printf("==== All Students ====\n");
    printf("ID: Age: Name:\n");
    while (db_size > 0)
    {
        student_t student = {0};
        if (1 != fread(&student, sizeof(student_t), 1, db))
        {
            printf("Error printing all students!\n");
            return -1;
        }
        printf("%-*d%-*d%s\n", 4, student.id, 4, student.age, student.name);
        db_size -= sizeof(student_t);
    }
    printf("======================\n");

    fclose(db);
    return 0;
}

static int printOneStudent(void)
{
    FILE *db = fopen(DB_FILE_NAME, "rb");
    if (NULL == db)
    {
        printf("Error printing all students!\n");
        return -1;
    }
    if (0 != fseek(db, 0, SEEK_END))
    {
        printf("Error seeking!\n");
        return -1;
    }

    long db_size = ftell(db);
    if (0 != fseek(db, 0, SEEK_SET))
    {
        printf("Error seeking!\n");
        return -1;
    }

    int id;
    printf("Enter id: ");
    if (1 != scanf("%d", &id))
    {
        printf("Error getting input!\n");
        return -1;
    }
    getchar();

    while (db_size > 0)
    {
        student_t student = {0};
        if (1 != fread(&student, sizeof(student_t), 1, db))
        {
            printf("Error printing all students!\n");
            return -1;
        }
        if (student.id == id)
        {
            printf("=== Chosen Student ===\n");
            printf("ID: Age: Name:\n");
            printf("%-*d%-*d%s\n", 4, student.id, 4, student.age, student.name);
            printf("======================\n");
            break;
        }
        db_size -= sizeof(student_t);
    }
    if (db_size == 0)
    {
        printf("Not valid id!\n");
    }

    fclose(db);
    return 0;
}

static int editStudent(void)
{
    FILE *db = fopen(DB_FILE_NAME, "r+b");
    if (NULL == db)
    {
        printf("Error printing all students!\n");
        return -1;
    }
    if (0 != fseek(db, 0, SEEK_END))
    {
        printf("Error seeking!\n");
        return -1;
    }

    long db_size = ftell(db);
    if (0 != fseek(db, 0, SEEK_SET))
    {
        printf("Error seeking!\n");
        return -1;
    }

    student_t new_student = {0};
    printf("Enter id: ");
    if (1 != scanf("%d", &new_student.id))
    {
        printf("Error getting input!\n");
        return -1;
    }
    getchar();

    while (db_size > 0)
    {
        long saved_pos = ftell(db);
        student_t student = {0};
        if (1 != fread(&student, sizeof(student_t), 1, db))
        {
            printf("Error printing all students!\n");
            return -1;
        }
        if (student.id == new_student.id)
        {
            int age = 0;
            char age_str[20];
            printf("Enter Age: ");
            fgets(age_str, sizeof(age_str), stdin);
            for (int i = 0; i < sizeof(age_str); i++)
            {
                if (isdigit(age_str[i]))
                {
                    age *= 10;
                    age += age_str[i] - '0';
                }
            }
            if (age != 0)
            {
                if (age >= 5 && age <= 75)
                {
                    new_student.age = age;
                }
                else
                {
                    new_student.age = student.age;
                }
            }
            else
            {
                new_student.age = student.age;
            }

            printf("Enter Name: ");
            fgets(new_student.name, NAME_LEN + 1, stdin);
            for (int i = NAME_LEN; i >= 0; i--)
            {
                if (new_student.name[i] != '\0' && new_student.name[i] != '\n')
                {
                    break;
                }
                new_student.name[i] = '\0';
            }
            if (new_student.name[0] == '\0')
            {
                strcpy(new_student.name, student.name);
            }

            if (0 != fseek(db, saved_pos, SEEK_SET))
            {
                printf("Error seeking!\n");
                return -1;
            }
            if (1 != fwrite(&new_student, sizeof(student_t), 1, db))
            {
                printf("Error editing student!\n");
                return -1;
            }
            printf("Student edited\n");
            break;
        }
        db_size -= sizeof(student_t);
    }
    if (db_size == 0)
    {
        printf("Not valid id!\n");
    }

    fclose(db);
    return 0;
}

int main(void)
{
    FILE *db = fopen(DB_FILE_NAME, "ab");
    if (NULL == db)
    {
        printf("Error opening " DB_FILE_NAME "!\n");
        return -1;
    }
    fclose(db);

    int greatest_id = getGreatestId();

    while (1)
    {
        printMenu();

        char Menu;
        scanf("%c", &Menu);
        getchar();

        if (Menu == 'a' || Menu == 'A')
        {
            if (-1 == printAllStudents())
            {
                return -1;
            }
            continue;
        }

        if (Menu == 'c' || Menu == 'C')
        {
            greatest_id += 1;
            if (-1 == createStudent(greatest_id))
            {
                return -1;
            }
            continue;
        }

        if (Menu == 'p' || Menu == 'P')
        {
            if (-1 == printOneStudent())
            {
                return -1;
            }
            continue;
        }

        if (Menu == 'e' || Menu == 'E')
        {
            if (-1 == editStudent())
            {
                return -1;
            }
            continue;
        }

        if (Menu == 'q' || Menu == 'Q')
        {
            printf("Closed\n");
            return 0;
        }
    }
}