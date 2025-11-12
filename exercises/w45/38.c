/**
 * @file exercise-38.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of file handling in C
 *        1) Make an array(users) of user_t
 *        2) Make a function to fill users with random names and unique ids started from 1
 *        3) Make a function to print the users
 *        4) Make a function to write users to a binary file
 *        5) Make a function to read the users from the file
 *        6) Make a function to change a user name based on its id
 *
 * @version 0.1
 * @date 2021-03-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USERS       4U
#define NAME_LEN    8U
#define ALPHABETS   26
#define FILENAME    "users.bin"
#define USER_FORMAT "%u: %s\n"

typedef struct {
    uint32_t id;
    char name[NAME_LEN + 1];
} user_t;

static bool fill_users(size_t len, user_t *arr);
static bool print_users(size_t len, const user_t *arr);
static bool write_users(size_t len, const user_t *arr);
static bool read_users(size_t len, user_t *arr);
static bool update_user(uint32_t id, const char *name);

int main(void)
{
    user_t users[USERS] = {0};

    if (!fill_users(USERS, users))
    {
        (void)printf("Failed to fill the array!\n");
        exit(1);
    }

    if (!print_users(USERS, users))
    {
        (void)printf("Failed to print users!\n");
        exit(1);
    }

    if (!write_users(USERS, users))
    {
        (void)printf("Failed to write users to the file!\n");
        exit(1);
    }

    if (!read_users(USERS, users))
    {
        (void)printf("Failed to read users from the file!\n");
        exit(1);
    }

    (void)printf("\n");

    if (!print_users(USERS, users))
    {
        (void)printf("Failed to print users!\n");
        exit(1);
    }

    if (!update_user(3, "Abcdefgh"))
    {
        (void)printf("Failed to update the user!\n");
        exit(1);
    }

    if (!read_users(USERS, users))
    {
        (void)printf("Failed to read users from the file!\n");
        exit(1);
    }

    (void)printf("\n");

    if (!print_users(USERS, users))
    {
        (void)printf("Failed to print users!\n");
        exit(1);
    }

    return 0;
}

static bool fill_users(size_t len, user_t *arr)
{
    bool status = false;
    if (!arr || len == 0)
    {
        return status;
    }
    time_t seed = time(NULL);

    for (user_t *u = arr; u < (arr + len); u++)
    {
        for (char *p = u->name; p < (u->name + NAME_LEN); p++)
        {
            srand(seed);
            *p = ((rand() - 97) % ALPHABETS + ALPHABETS) % ALPHABETS + 97;
            seed = (seed >> 4) * *p;
        }
        u->name[NAME_LEN] = '\0';
        u->id = (uint32_t)(u - arr) + 1u;
    }
    status = true;
    return status;
}

static bool print_users(size_t len, const user_t *arr)
{
    bool status = false;
    if (!arr || len == 0)
    {
        return status;
    }
    for (const user_t *u = arr; u < (arr + len); u++)
    {
        printf(USER_FORMAT, u->id, u->name);
    }
    status = true;
    return status;
}

static bool write_users(size_t len, const user_t *arr)
{
    bool status = false;
    if (!arr || len == 0)
    {
        return status;
    }
    FILE *fp = fopen(FILENAME, "wb");
    if (!fp)
    {
        return status;
    }

    for (const user_t *u = arr; u < (arr + len); u++)
    {
        status = false;
        if (fwrite(&u->id, sizeof(u->id), 1, fp) != 1)
        {
            break;
        }
        if (fseek(fp, 4, SEEK_CUR) == -1)
        {
            break;
        }
        if (fwrite(u->name, NAME_LEN, 1, fp) != 1)
        {
            break;
        }
        status = true;
    }

    fclose(fp);
    return status;
}

static bool read_users(size_t len, user_t *arr)
{
    bool status = false;
    if (!arr || len == 0)
    {
        return status;
    }
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp)
    {
        return status;
    }

    for (user_t *u = arr; !feof(fp) && u < (arr + len); u++)
    {
        status = false;
        if (fread(&u->id, sizeof(u->id), 1, fp) != 1)
        {
            break;
        }
        if (fseek(fp, 4, SEEK_CUR) == -1)
        {
            break;
        }
        if (fread(u->name, NAME_LEN, 1, fp) != 1)
        {
            break;
        }
        status = true;
    }

    fclose(fp);
    return status;
}

static bool update_user(uint32_t id, const char *name)
{
    bool status = false;
    if (!name || id == 0)
    {
        return status;
    }

    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp)
    {
        return status;
    }

    user_t u = {0};
    while (!feof(fp) && u.id != id)
    {
        status = false;
        if (fread(&u.id, sizeof(u.id), 1, fp) != 1)
        {
            break;
        }
        if (fseek(fp, 4, SEEK_CUR) == -1)
        {
            break;
        }
        long pos = ftell(fp);
        if (fread(u.name, NAME_LEN, 1, fp) != 1)
        {
            break;
        }
        if (u.id == id)
        {
            if (fseek(fp, pos, SEEK_SET) == -1)
            {
                break;
            }
            if (fwrite(name, NAME_LEN, 1, fp) != 1)
            {
                break;
            }
        }
        status = true;
    }

    fclose(fp);
    return status;
}
