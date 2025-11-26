/*
 * Simple student database with binary file storage.
 *
 * Requirements:
 *  - Student records are stored in a binary file.
 *  - Each student has:
 *      - ID: unique integer > 0, generated automatically
 *      - Name: string, max 32 characters, not empty
 *      - Age: integer 5..75
 *  - Menu:
 *      A/a: Print all students
 *      C/c: Create a student
 *      P/p: Print a student by ID
 *      E/e: Edit a student by ID
 *      D/d: Delete a student by ID (VG requirement)
 *      Q/q: Quit
 *  - Input validation and file I/O error handling.
 *
 * NOTE ABOUT FILE FORMAT
 * ----------------------
 * The binary file has this layout:
 *
 *  [FileHeader][Student][Student][Student]...
 *
 * FileHeader:
 *      int32_t next_id;  // the next unused ID value
 *      int32_t count;    // number of students currently stored
 *
 * Student:
 *      int32_t id;
 *      int32_t age;
 *      char    name[33]; // 32 chars + terminating '\0'
 *
 * This program is self-consistent: it both writes and reads using the same
 * struct layout. Padding inside the structs is therefore not a problem here.
 */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------- */
/*                           DATA STRUCTURES                                 */
/* ------------------------------------------------------------------------- */

/* The header stored at the beginning of the binary file. */
typedef struct {
    int32_t next_id; /* next ID that will be assigned to a new student */
    int32_t count;   /* number of students currently stored */
} FileHeader;

/* A single student record. */
typedef struct {
    int32_t id;    /* Unique ID > 0 */
    int32_t age;   /* 5..75 */
    char name[33]; /* Up to 32 chars + '\0' */
} Student;

/* Name of the binary file used to store everything. */
static const char *STUDENT_DB_FILENAME = "students.bin";

/* ------------------------------------------------------------------------- */
/*                      SMALL UTILITY / HELPER FUNCTIONS                     */
/* ------------------------------------------------------------------------- */

/*
 * Reads a line from stdin into 'buffer', at most 'size' bytes including '\0'.
 * It strips the trailing newline, if there is one.
 *
 * Return value:
 *  - true  if a line was read successfully
 *  - false on EOF or error
 */
static bool read_line(char *buffer, size_t size)
{
    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        return false; /* EOF or error */
    }

    /* Remove trailing '\n', if present. */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    return true;
}

/*
 * Reads an integer from stdin with validation.
 *
 * Parameters:
 *  - prompt: text to show to the user
 *  - allow_empty: if true, empty input is allowed and *is_empty is set
 *  - min_value, max_value: valid range when non-empty
 *  - out_value: where the parsed int is stored
 *  - is_empty: set to true if the user entered an empty line (only if allowed)
 *
 * This function keeps asking until valid input is entered or EOF occurs.
 *
 * Return value:
 *  - true  on success
 *  - false on EOF or input error (caller should usually abort in that case)
 */
static bool read_int_with_range(const char *prompt, bool allow_empty, int min_value, int max_value, int *out_value,
                                bool *is_empty)
{
    char buf[128];

    for (;;)
    {
        printf("%s", prompt);
        fflush(stdout);

        if (!read_line(buf, sizeof buf))
        {
            /* EOF or error */
            return false;
        }

        if (allow_empty && buf[0] == '\0')
        {
            /* User pressed Enter on an empty line */
            if (is_empty)
            {
                *is_empty = true;
            }
            return true;
        }

        char *endptr = NULL;
        errno = 0;
        long val = strtol(buf, &endptr, 10);

        if (errno != 0)
        {
            perror("strtol");
            printf("Please enter a valid integer.\n");
            continue;
        }

        /* Check that the whole string was consumed (no garbage at the end). */
        while (*endptr != '\0' && isspace((unsigned char)*endptr))
        {
            endptr++;
        }
        if (*endptr != '\0')
        {
            printf("Invalid input: extra characters after the number.\n");
            continue;
        }

        if (val < min_value || val > max_value)
        {
            printf("Please enter a value between %d and %d.\n", min_value, max_value);
            continue;
        }

        *out_value = (int)val;
        if (is_empty)
        {
            *is_empty = false;
        }
        return true;
    }
}

/*
 * Reads a name string from stdin, with length and emptiness checks.
 *
 * Parameters:
 *  - prompt: text to show
 *  - allow_empty: if true, user may press Enter to "keep old value"
 *  - max_len: maximum allowed length (not counting '\0')
 *  - out_name: buffer where the result is stored
 *  - out_is_empty: set to true if user entered an empty line when allowed
 *
 * Return value:
 *  - true  on success
 *  - false on EOF or error
 */
static bool read_name(const char *prompt, bool allow_empty, size_t max_len, char *out_name, bool *out_is_empty)
{
    char buf[256];

    for (;;)
    {
        printf("%s", prompt);
        fflush(stdout);

        if (!read_line(buf, sizeof buf))
        {
            return false;
        }

        if (buf[0] == '\0')
        {
            /* User entered empty line. */
            if (allow_empty)
            {
                if (out_is_empty)
                {
                    *out_is_empty = true;
                }
                return true;
            }
            else
            {
                printf("Name must not be empty.\n");
                continue;
            }
        }

        size_t len = strlen(buf);
        if (len > max_len)
        {
            printf("Name too long (max %zu characters).\n", max_len);
            continue;
        }

        strncpy(out_name, buf, max_len + 1);
        out_name[max_len] = '\0'; /* just in case */
        if (out_is_empty)
        {
            *out_is_empty = false;
        }
        return true;
    }
}

/* ------------------------------------------------------------------------- */
/*                             FILE OPERATIONS                               */
/* ------------------------------------------------------------------------- */

/*
 * Opens the student database file.
 *
 * If the file does not exist, it is created and an initial header is written.
 *
 * Return value:
 *  - FILE* on success (opened in "rb+")
 *  - NULL on error (error message already printed)
 */
static FILE *open_database(const char *filename)
{
    /* First attempt to open an existing file in read/write binary mode. */
    FILE *fp = fopen(filename, "rb+");
    if (fp != NULL)
    {
        return fp;
    }

    /* If fopen failed for another reason than "file does not exist", report it. */
    if (errno != ENOENT)
    {
        perror("fopen");
        return NULL;
    }

    /* File does not exist; create it. */
    fp = fopen(filename, "wb+");
    if (fp == NULL)
    {
        perror("fopen");
        return NULL;
    }

    /* Initialize header: next_id starts at 1, count = 0. */
    FileHeader header;
    header.next_id = 1;
    header.count = 0;

    if (fwrite(&header, sizeof header, 1, fp) != 1)
    {
        perror("fwrite");
        fclose(fp);
        return NULL;
    }

    /* Ensure it is written. */
    if (fflush(fp) != 0)
    {
        perror("fflush");
        fclose(fp);
        return NULL;
    }

    /* Rewind to the start so caller sees file from the beginning. */
    rewind(fp);
    return fp;
}

/*
 * Reads the header from the already-open database file.
 * The file position is assumed to be at the beginning or anywhere; this
 * function seeks to the start.
 *
 * Return value:
 *  - true  on success
 *  - false on error
 */
static bool read_header(FILE *fp, FileHeader *header)
{
    if (fseek(fp, 0L, SEEK_SET) != 0)
    {
        perror("fseek");
        return false;
    }
    if (fread(header, sizeof *header, 1, fp) != 1)
    {
        if (feof(fp))
        {
            fprintf(stderr, "Error: database file is truncated.\n");
        }
        else
        {
            perror("fread");
        }
        return false;
    }
    return true;
}

/*
 * Writes the header to the already-open database file.
 * This function rewinds to the beginning before writing.
 *
 * Return value:
 *  - true  on success
 *  - false on error
 */
static bool write_header(FILE *fp, const FileHeader *header)
{
    if (fseek(fp, 0L, SEEK_SET) != 0)
    {
        perror("fseek");
        return false;
    }
    if (fwrite(header, sizeof *header, 1, fp) != 1)
    {
        perror("fwrite");
        return false;
    }
    if (fflush(fp) != 0)
    {
        perror("fflush");
        return false;
    }
    return true;
}

/*
 * Moves the file position to the beginning of the first Student record.
 * That is, it seeks to sizeof(FileHeader).
 *
 * Return value:
 *  - true  on success
 *  - false on error
 */
static bool seek_to_first_student(FILE *fp)
{
    if (fseek(fp, (long)sizeof(FileHeader), SEEK_SET) != 0)
    {
        perror("fseek");
        return false;
    }
    return true;
}

/* ------------------------------------------------------------------------- */
/*                           PRINTING FUNCTIONS                              */
/* ------------------------------------------------------------------------- */

/*
 * Prints a single student in a formatted way.
 */
static void print_student(const Student *s)
{
    printf("ID:   %d\n", s->id);
    printf("Name: %s\n", s->name);
    printf("Age:  %d\n", s->age);
    printf("---------------------------\n");
}

/*
 * Prints all students in the database.
 *
 * It:
 *  - opens the database
 *  - reads the header
 *  - iterates over all Student structs and prints them
 */
static void handle_print_all(void)
{
    FILE *fp = open_database(STUDENT_DB_FILENAME);
    if (!fp)
    {
        return;
    }

    FileHeader header;
    if (!read_header(fp, &header))
    {
        fclose(fp);
        return;
    }

    if (header.count == 0)
    {
        printf("No students in database.\n");
        fclose(fp);
        return;
    }

    if (!seek_to_first_student(fp))
    {
        fclose(fp);
        return;
    }

    printf("Number of students: %d\n", header.count);
    printf("=========================================\n");

    Student s;
    int printed = 0;

    while (fread(&s, sizeof s, 1, fp) == 1)
    {
        print_student(&s);
        printed++;
    }

    if (printed != header.count)
    {
        fprintf(stderr, "Warning: header.count = %d but read %d students.\n", header.count, printed);
    }

    fclose(fp);
}

/* ------------------------------------------------------------------------- */
/*                           CREATE NEW STUDENT                              */
/* ------------------------------------------------------------------------- */

/*
 * Handles the "Create A Student" menu option.
 *
 * Steps:
 *  - open database
 *  - read header
 *  - ask user for name and age with validation
 *  - fill Student struct
 *  - append it to the file
 *  - update header (next_id and count)
 */
static void handle_create_student(void)
{
    FILE *fp = open_database(STUDENT_DB_FILENAME);
    if (!fp)
    {
        return;
    }

    FileHeader header;
    if (!read_header(fp, &header))
    {
        fclose(fp);
        return;
    }

    /* Read name and age from user. */
    char name[33];
    bool dummy_empty = false; /* unused for create */

    if (!read_name("Enter name (max 32 chars): ",
                   /*allow_empty=*/false, 32, name, &dummy_empty))
    {
        printf("Input error, aborting.\n");
        fclose(fp);
        return;
    }

    int age = 0;
    bool dummy_empty_int = false; /* unused for create */

    if (!read_int_with_range("Enter age (5..75): ",
                             /*allow_empty=*/false, 5, 75, &age, &dummy_empty_int))
    {
        printf("Input error, aborting.\n");
        fclose(fp);
        return;
    }

    /* Prepare the new student. */
    Student s;
    s.id = header.next_id;
    s.age = age;
    strncpy(s.name, name, sizeof s.name);
    s.name[sizeof s.name - 1] = '\0';

    /* Append to the end of file. */
    if (fseek(fp, 0L, SEEK_END) != 0)
    {
        perror("fseek");
        fclose(fp);
        return;
    }

    if (fwrite(&s, sizeof s, 1, fp) != 1)
    {
        perror("fwrite");
        fclose(fp);
        return;
    }

    if (fflush(fp) != 0)
    {
        perror("fflush");
        fclose(fp);
        return;
    }

    /* Update header: increment next_id and count. */
    header.next_id++;
    header.count++;

    if (!write_header(fp, &header))
    {
        fclose(fp);
        return;
    }

    printf("Student created with ID %d.\n", s.id);

    fclose(fp);
}

/* ------------------------------------------------------------------------- */
/*                 FIND / PRINT / EDIT / DELETE BY ID                        */
/* ------------------------------------------------------------------------- */

/*
 * Helper: find a student by ID.
 *
 * Parameters:
 *  - fp: open FILE* already pointing somewhere inside the db
 *  - id: ID to look for
 *  - out_student: where to copy the student when found
 *  - out_offset: byte offset in the file where this Student begins
 *
 * Implementation:
 *  - start scanning from the first Student record
 *  - for each Student, check its id
 *  - if equal, remember the offset and copy to out_student
 *
 * Return value:
 *  - true  if found
 *  - false otherwise
 */
static bool find_student_by_id(FILE *fp, int id, Student *out_student, long *out_offset)
{
    if (!seek_to_first_student(fp))
    {
        return false;
    }

    Student s;
    long offset = ftell(fp);
    if (offset < 0)
    {
        perror("ftell");
        return false;
    }

    while (fread(&s, sizeof s, 1, fp) == 1)
    {
        if (s.id == id)
        {
            if (out_student)
            {
                *out_student = s;
            }
            if (out_offset)
            {
                *out_offset = offset;
            }
            return true;
        }

        offset = ftell(fp);
        if (offset < 0)
        {
            perror("ftell");
            return false;
        }
    }

    if (ferror(fp))
    {
        perror("fread");
    }

    return false;
}

/*
 * Handles "Print A Student" menu option.
 */
static void handle_print_student(void)
{
    FILE *fp = open_database(STUDENT_DB_FILENAME);
    if (!fp)
    {
        return;
    }

    FileHeader header;
    if (!read_header(fp, &header))
    {
        fclose(fp);
        return;
    }

    if (header.count == 0)
    {
        printf("No students in database.\n");
        fclose(fp);
        return;
    }

    int id = 0;
    bool is_empty = false;
    if (!read_int_with_range("Enter student ID: ",
                             /*allow_empty=*/false, 1, 2147483647, &id, &is_empty))
    {
        printf("Input error.\n");
        fclose(fp);
        return;
    }

    Student s;
    if (!find_student_by_id(fp, id, &s, NULL))
    {
        printf("No student with ID %d.\n", id);
        fclose(fp);
        return;
    }

    print_student(&s);

    fclose(fp);
}

/*
 * Handles "Edit A Student" menu option.
 *
 * Logic:
 *  - Ask for ID
 *  - Find student
 *  - Ask for new age (user may press Enter to keep old)
 *  - Ask for new name (user may press Enter to keep old)
 *  - Overwrite the Student record in the file
 */
static void handle_edit_student(void)
{
    FILE *fp = open_database(STUDENT_DB_FILENAME);
    if (!fp)
    {
        return;
    }

    FileHeader header;
    if (!read_header(fp, &header))
    {
        fclose(fp);
        return;
    }

    if (header.count == 0)
    {
        printf("No students in database.\n");
        fclose(fp);
        return;
    }

    int id = 0;
    bool is_empty = false;

    if (!read_int_with_range("Enter student ID to edit: ",
                             /*allow_empty=*/false, 1, 2147483647, &id, &is_empty))
    {
        printf("Input error.\n");
        fclose(fp);
        return;
    }

    Student s;
    long offset = 0;

    if (!find_student_by_id(fp, id, &s, &offset))
    {
        printf("No student with ID %d.\n", id);
        fclose(fp);
        return;
    }

    printf("Current data:\n");
    print_student(&s);

    /* Ask for new age (blank = keep old). */
    int new_age = s.age;
    bool age_empty = false;

    if (!read_int_with_range("Enter new age (5..75), or just Enter to keep current: ",
                             /*allow_empty=*/true, 5, 75, &new_age, &age_empty))
    {
        printf("Input error.\n");
        fclose(fp);
        return;
    }

    if (!age_empty)
    {
        s.age = new_age;
    }

    /* Ask for new name (blank = keep old). */
    char new_name[33];
    bool name_empty = false;

    if (!read_name("Enter new name (max 32 chars), or just Enter to keep current: ",
                   /*allow_empty=*/true, 32, new_name, &name_empty))
    {
        printf("Input error.\n");
        fclose(fp);
        return;
    }

    if (!name_empty)
    {
        strncpy(s.name, new_name, sizeof s.name);
        s.name[sizeof s.name - 1] = '\0';
    }

    /* Seek back to where this student record starts and overwrite it. */
    if (fseek(fp, offset, SEEK_SET) != 0)
    {
        perror("fseek");
        fclose(fp);
        return;
    }

    if (fwrite(&s, sizeof s, 1, fp) != 1)
    {
        perror("fwrite");
        fclose(fp);
        return;
    }

    if (fflush(fp) != 0)
    {
        perror("fflush");
        fclose(fp);
        return;
    }

    printf("Student with ID %d updated.\n", s.id);

    fclose(fp);
}

/*
 * Handles "Delete A Student" menu option (VG requirement).
 *
 * Implementation strategy:
 *  - Open the existing database.
 *  - Read header.
 *  - Open a temporary file.
 *  - Write a new header to the temporary file.
 *  - Copy all students EXCEPT the one with the given ID into the temp file,
 *    updating the 'count' field.
 *  - Close both files.
 *  - Replace the original file with the temp file (using rename()).
 */
static void handle_delete_student(void)
{
    FILE *fp = open_database(STUDENT_DB_FILENAME);
    if (!fp)
    {
        return;
    }

    FileHeader header;
    if (!read_header(fp, &header))
    {
        fclose(fp);
        return;
    }

    if (header.count == 0)
    {
        printf("No students in database.\n");
        fclose(fp);
        return;
    }

    int id = 0;
    bool is_empty = false;

    if (!read_int_with_range("Enter student ID to delete: ",
                             /*allow_empty=*/false, 1, 2147483647, &id, &is_empty))
    {
        printf("Input error.\n");
        fclose(fp);
        return;
    }

    /* Temporary file name. In a real program you might want something safer. */
    const char *tmp_name = "students.tmp";

    FILE *tmp = fopen(tmp_name, "wb");
    if (!tmp)
    {
        perror("fopen (tmp)");
        fclose(fp);
        return;
    }

    /* We'll reuse the same next_id; only count will change. */
    FileHeader new_header = header;
    new_header.count = 0;

    if (fwrite(&new_header, sizeof new_header, 1, tmp) != 1)
    {
        perror("fwrite (header)");
        fclose(tmp);
        fclose(fp);
        return;
    }

    if (!seek_to_first_student(fp))
    {
        fclose(tmp);
        fclose(fp);
        return;
    }

    Student s;
    bool found = false;

    while (fread(&s, sizeof s, 1, fp) == 1)
    {
        if (s.id == id)
        {
            found = true;
            /* Skip copying this one (i.e., delete it). */
            continue;
        }

        if (fwrite(&s, sizeof s, 1, tmp) != 1)
        {
            perror("fwrite (student)");
            fclose(tmp);
            fclose(fp);
            return;
        }

        new_header.count++;
    }

    if (ferror(fp))
    {
        perror("fread");
        fclose(tmp);
        fclose(fp);
        return;
    }

    if (!found)
    {
        printf("No student with ID %d.\n", id);
        fclose(tmp);
        fclose(fp);
        /* Delete the incomplete temp file. */
        (void)remove(tmp_name);
        return;
    }

    /* Rewrite header in the temp file with updated count. */
    if (fseek(tmp, 0L, SEEK_SET) != 0)
    {
        perror("fseek (tmp)");
        fclose(tmp);
        fclose(fp);
        return;
    }

    if (fwrite(&new_header, sizeof new_header, 1, tmp) != 1)
    {
        perror("fwrite (new header)");
        fclose(tmp);
        fclose(fp);
        return;
    }

    if (fflush(tmp) != 0)
    {
        perror("fflush (tmp)");
        fclose(tmp);
        fclose(fp);
        return;
    }

    fclose(tmp);
    fclose(fp);

    /* Replace original file with temp file. */
    if (remove(STUDENT_DB_FILENAME) != 0)
    {
        perror("remove");
        /* best effort: temp file still exists */
        return;
    }

    if (rename(tmp_name, STUDENT_DB_FILENAME) != 0)
    {
        perror("rename");
        /* again, best effort; database might be missing now */
        return;
    }

    printf("Student with ID %d deleted.\n", id);
}

/* ------------------------------------------------------------------------- */
/*                               MENU LOGIC                                  */
/* ------------------------------------------------------------------------- */

/*
 * Prints the menu to the terminal.
 */
static void print_menu(void)
{
    printf("\n");
    printf("==== Student Database Menu ====\n");
    printf("A) Print All Students\n");
    printf("C) Create A Student\n");
    printf("P) Print A Student\n");
    printf("E) Edit A Student\n");
    printf("D) Delete A Student\n"); /* VG option */
    printf("Q) Quit\n");
    printf("Select option: ");
    fflush(stdout);
}

/*
 * Reads a single character from stdin to select a menu item.
 * We read an entire line and take the first non-whitespace character.
 *
 * Return value:
 *  - the chosen character in lowercase, or '\0' on EOF/error.
 */
static char read_menu_choice(void)
{
    char buf[64];

    if (!read_line(buf, sizeof buf))
    {
        return '\0'; /* EOF or error */
    }

    for (size_t i = 0; buf[i] != '\0'; i++)
    {
        if (!isspace((unsigned char)buf[i]))
        {
            return (char)tolower((unsigned char)buf[i]);
        }
    }

    return '\0'; /* no non-space characters */
}

/* ------------------------------------------------------------------------- */
/*                                   main                                    */
/* ------------------------------------------------------------------------- */

int main(void)
{
    for (;;)
    {
        print_menu();
        char choice = read_menu_choice();
        if (choice == '\0')
        {
            printf("End of input. Quitting.\n");
            break;
        }

        switch (choice)
        {
            case 'a': handle_print_all(); break;
            case 'c': handle_create_student(); break;
            case 'p': handle_print_student(); break;
            case 'e': handle_edit_student(); break;
            case 'd': handle_delete_student(); break;
            case 'q': printf("Goodbye.\n"); return 0;
            default: printf("Unknown option '%c'. Please try again.\n", choice); break;
        }
    }

    return 0;
}
