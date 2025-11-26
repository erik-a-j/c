#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRINGIFY_(x)      #x
#define STRINGIFY(x)       STRINGIFY_(x)

#define DB_FILE            "students.bin"
#define NAME_LEN           32
#define PRINT_STUDENTS_ALL 0

typedef struct {
    int id;
    int age;
    char name[NAME_LEN + 1];
} student_t;

static int get_db_entry_count(void)
{
    int count = 0;
    long off = 0;
    FILE *fp = fopen(DB_FILE, "ab");
    if (fp)
    {
        off = ftell(fp);
        if (0 < off)
        {
            if (0 == off % sizeof(student_t))
            {
                count = (int)(off / sizeof(student_t));
            }
            else
            {
                fprintf(stderr, "database is corrupted\n");
                count = -1;
            }
        }
        fclose(fp);
    }
    return count;
}
static bool get_student(student_t *student, size_t *index, FILE *fp)
{
    if (!student || !fp)
    {
        fprintf(stderr, "Invalid arguments\n");
        return false;
    }
    long saved_off = ftell(fp);
    if (0 != fseek(fp, 0, SEEK_END))
    {
        fprintf(stderr, "failed to seek\n");
        return false;
    }
    long end_off = ftell(fp);
    if (0 != fseek(fp, saved_off, SEEK_SET))
    {
        fprintf(stderr, "failed to seek\n");
        return false;
    }
    bool status = true;
    int id = 0;
    while (0 == id) // skip deleted entries
    {
        if (*index * sizeof(student_t) < (size_t)end_off)
        {
            if (1 != fread(student, sizeof(student_t), 1, fp))
            {
                fprintf(stderr, "failed to read\n");
                status = false;
            }
            id = student->id;
            (*index)++;
        }
        else
        {
            status = false;
            break;
        }
    }
    return status;
}
static bool id_exists(int id)
{
    bool status = true;
    size_t index = 0;
    student_t student = {0};
    FILE *fp = fopen(DB_FILE, "rb");
    if (fp)
    {
        while (get_student(&student, &index, fp))
        {
            if (id == student.id)
            {
                break;
            }
        }
        fclose(fp);
    }
    else
    {
        fprintf(stderr, "failed to open database: %s\n", DB_FILE);
        status = false;
    }
    if (id != student.id)
    {
        status = false;
    }
    return status;
}
static bool get_unique_id(int *id)
{
    bool status = true;
    int greatest_id = 0;
    int entry_count = get_db_entry_count();
    if (0 < entry_count)
    {
        FILE *fp = fopen(DB_FILE, "rb");
        if (fp)
        {
            int nread = 0;
            student_t student = {0};
            while (nread < entry_count && 0 == feof(fp) && 0 == ferror(fp))
            {
                if (1 != fread(&student, sizeof(student_t), 1, fp))
                {
                    status = false;
                    break;
                }
                if (student.id > greatest_id)
                {
                    greatest_id = student.id;
                }
                nread++;
            }
            fclose(fp);
        }
        else
        {
            fprintf(stderr, "failed to read database\n");
            status = false;
        }
    }
    *id = greatest_id + 1;
    return status;
}
static bool update_student(student_t *new_student, int id)
{
    if (!new_student)
    {
        fprintf(stderr, "student is NULL\n");
        return false;
    }
    bool status = true;
    size_t index = 0;
    student_t student = {0};
    FILE *fp = fopen(DB_FILE, "r+b");
    if (fp)
    {
        while (get_student(&student, &index, fp))
        {
            if (student.id == id)
            {
                if (0 == fseek(fp, -(sizeof(student_t)), SEEK_CUR))
                {
                    if (1 != fwrite(new_student, sizeof(student_t), 1, fp))
                    {
                        fprintf(stderr, "failed to write new_student\n");
                        status = false;
                    }
                }
                else
                {
                    fprintf(stderr, "failed to seek\n");
                    status = false;
                }
                break;
            }
        }
        fclose(fp);
    }
    return status;
}
static bool save_student(student_t *student)
{
    bool status = true;
    FILE *fp = fopen(DB_FILE, "ab");
    if (fp)
    {
        if (0 == ftell(fp) % sizeof(student_t))
        {
            if (1 != fwrite(student, sizeof(student_t), 1, fp))
            {
                fprintf(stderr, "failed to write student to database\n");
                status = false;
            }
        }
        else
        {
            fprintf(stderr, "database is corrupted\n");
            status = false;
        }
        fclose(fp);
    }
    else
    {
        fprintf(stderr, "failed to open %s\n", DB_FILE);
        status = false;
    }

    return status;
}
static bool fill_student(student_t *student)
{
    bool status = true;
    if (student)
    {
        bool correct = false;
        while (!correct)
        {
            char age_str[10] = {0};
            printf("Enter age: ");
            // get age as a string first to be able to treat empty input as a no-operation
            if (!fgets(age_str, sizeof(age_str), stdin))
            {
                fprintf(stderr, "failed to get age input\n");
                status = false;
                break;
            }
            if (age_str[0] == '\n') // empty input
            {
                student->age = 0;
                break;
            }
            if (age_str[0] >= '0' && age_str[0] <= '9')
            {
                student->age = age_str[0] - '0'; // convert ascii to int
                if (age_str[1] >= '0' && age_str[1] <= '9')
                {
                    student->age *= 10;               // multiply by 10 to correctly construct the final int
                    student->age += age_str[1] - '0'; // convert ascii to int
                }
            }
            if (student->age < 5 || student->age > 75)
            {
                continue;
            }
            correct = true;
        }
        correct = false;
        while (!correct)
        {
            char name[NAME_LEN * 2] = {0}; // bigger buffer to hopefully empty stdin
            printf("Enter name: ");
            if (!fgets(name, NAME_LEN * 2, stdin))
            {
                status = false;
                break;
            }
            if ('\0' != name[NAME_LEN + 1] && '\n' != name[NAME_LEN + 1]) // detect name lenght overflow
            {
                continue;
            }
            for (char *p = name + NAME_LEN + 1; p >= name; p--) // trim trailing newlines
            {
                if (*p == '\n')
                {
                    *p = '\0';
                }
                if (*p != '\0')
                {
                    break;
                }
            }
            if (!strncpy(student->name, name, NAME_LEN))
            {
                fprintf(stderr, "failed to copy string\n");
                status = false;
                break;
            }
            student->name[NAME_LEN] = '\0';
            correct = true;
            for (char *p = student->name + NAME_LEN; p >= student->name; p--)
            {
                if (*p == '\0')
                {
                    if (p == student->name) // no-op
                    {
                        break;
                    }
                    continue;
                }
                if (!((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || *p == ' ')) // allowed characters in name
                {
                    correct = false;
                    break;
                }
            }
        }
    }
    else
    {
        fprintf(stderr, "student is NULL\n");
        status = false;
    }
    return status;
}
static bool new_student(void)
{
    bool status = true;
    student_t student = {0};
    if (!get_unique_id(&student.id))
    {
        fprintf(stderr, "failed to get unique id\n");
        status = false;
    }
    else
    {
        if (fill_student(&student))
        {
            if (student.age != 0 && student.name[0] != '\0')
            {
                save_student(&student);
            }
        }
        else
        {
            fprintf(stderr, "failed to fill student\n");
            status = false;
        }
    }
    return status;
}
static bool edit_student(bool del)
{
    bool status = true;
    int id;
    printf("Enter ID: ");
    int res_scanf = scanf("%d", &id);
    (void)getchar();
    if (1 == res_scanf)
    {
        if (id_exists(id))
        {
            student_t student = {0};
            if (del || fill_student(&student))
            {
                if (del || (student.age != 0 && student.name[0] != '\0'))
                {
                    if (!del)
                    {
                        student.id = id;
                    }
                    if (!update_student(&student, id))
                    {
                        fprintf(stderr, "failed to update student\n");
                        status = false;
                    }
                }
            }
            else
            {
                fprintf(stderr, "failed to fill student\n");
                status = false;
            }
        }
        else
        {
            fprintf(stderr, "no student with ID: %d found\n", id);
        }
    }
    else
    {
        fprintf(stderr, "failed to get input\n");
        status = false;
    }
    return status;
}

static void print_one_student(const student_t *student)
{
    if (!student)
    {
        fprintf(stderr, "student is NULL\n");
        return;
    }
    printf("ID: %d, age: %d, name: %s\n", student->id, student->age, student->name);
}
static bool print_students(int id) // id == PRINT_STUDENTS_ALL && print all
{
    bool status = true;
    bool id_found = false;
    int entry_count = get_db_entry_count();
    printf("%s:\n", (id != PRINT_STUDENTS_ALL) ? "Student" : "Students");
    if (0 < entry_count)
    {
        size_t index = 0;
        student_t student = {0};
        FILE *fp = fopen(DB_FILE, "rb");
        if (fp)
        {
            while (get_student(&student, &index, fp))
            {
                if (id == PRINT_STUDENTS_ALL || id == student.id)
                {
                    print_one_student(&student);
                    if (id != PRINT_STUDENTS_ALL)
                    {
                        id_found = true;
                        break;
                    }
                }
            }
            fclose(fp);
        }
    }
    if (status && id != PRINT_STUDENTS_ALL)
    {
        status = id_found;
    }
    return status;
}
static bool select_and_print_student(void)
{
    bool status = true;
    int id;
    printf("Enter ID: ");
    int res_scanf = scanf("%d", &id);
    (void)getchar();
    puts("");
    if (1 == res_scanf)
    {
        if (!id_exists(id))
        {
            fprintf(stderr, "no student with ID: %d found\n", id);
        }
        else if (!print_students(id))
        {
            fprintf(stderr, "failed to print student with ID: %d\n", id);
            status = false;
        }
    }
    else
    {
        fprintf(stderr, "failed to get input\n");
        status = false;
    }
    return status;
}
static void print_menu(void)
{
    printf("\nA) Print All Students\n"
           "C) Create A Student\n"
           "P) Print A Student\n"
           "E) Edit A Student\n"
           "D) Delete A Student\n"
           "Q) Quit\n"
           "Enter choice: ");
}

int main(void)
{
    int running = 1;
    while (running)
    {
        char ch;
        print_menu();
        int res_scanf = scanf(" %c", &ch); // capture choice but skip whitespaces
        (void)getchar();                   // clear the buffered newline
        if (1 != res_scanf)
        {
            fprintf(stderr, "failed to get input");
            break;
        }
        puts("");
        switch (ch)
        {
            case 'a': /* fall-through */
            case 'A': {
                if (!print_students(PRINT_STUDENTS_ALL))
                {
                    running = 0;
                }
                break;
            }
            case 'c': /* fall-through */
            case 'C': {
                if (!new_student())
                {
                    running = 0;
                }
                break;
            }
            case 'p': /* fall-through */
            case 'P': {
                if (!select_and_print_student())
                {
                    running = 0;
                }
                break;
            }
            case 'e': /* fall-through */
            case 'E': {
                if (!edit_student(false))
                {
                    running = 0;
                }
                break;
            }
            case 'd': /* fall-through */
            case 'D': {
                if (!edit_student(true))
                {
                    running = 0;
                }
                break;
            }
            case 'q': /* fall-through */
            case 'Q': {
                running = 0;
                break;
            }
        }
    }
    return 0;
}