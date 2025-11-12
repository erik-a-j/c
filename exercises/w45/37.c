/**
 * @file exercise-37.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of file handling in C
 *        1) Make an array(users) of user_t
 *        2) Make a function to fill users with random names and unique ids started from 1
 *        3) Make a function to print the users
 *        4) Make a function to write users to a text file
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
#define FILE_NAME   "users.txt"
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

int main(void) {
    user_t users[USERS] = {0};

    if (!fill_users(USERS, users)) {
        (void)printf("Failed to fill the array!\n");
        exit(1);
    }

    if (!print_users(USERS, users)) {
        (void)printf("Failed to print users!\n");
        exit(1);
    }

    if (!write_users(USERS, users)) {
        (void)printf("Failed to write users to the file!\n");
        exit(1);
    }

    if (!read_users(USERS, users)) {
        (void)printf("Failed to read users from the file!\n");
        exit(1);
    }

    (void)printf("\n");

    if (!print_users(USERS, users)) {
        (void)printf("Failed to print users!\n");
        exit(1);
    }

    if (!update_user(3, "Abcdefgh")) {
        (void)printf("Failed to update the user!\n");
        exit(1);
    }

    if (!read_users(USERS, users)) {
        (void)printf("Failed to read users from the file!\n");
        exit(1);
    }

    (void)printf("\n");

    if (!print_users(USERS, users)) {
        (void)printf("Failed to print users!\n");
        exit(1);
    }

    return 0;
}

static bool fill_users(size_t len, user_t *arr) {
    bool status = false;

    FILE *urand = fopen("/dev/urandom", "rb");
    if (!urand) {
        return status;
    }

    for (size_t i = 1; i <= len; i++) {
        user_t *user = &arr[i - 1];
        user->id = (uint32_t)i;

        if (fread(user->name, 1, NAME_LEN, urand) != NAME_LEN) {
            status = false;
            break;
        }
        for (int j = 0; j < NAME_LEN; j++) {
            user->name[j] = ((user->name[j] - 97) % ALPHABETS + ALPHABETS) % ALPHABETS + 97;
        }
        user->name[NAME_LEN] = '\0';
        status = true;
    }

    fclose(urand);
    return status;
}
static bool print_users(size_t len, const user_t *arr) {
    bool status = false;
    if (!arr || len == 0) {
        return status;
    }
    for (size_t i = 0; i < len; i++) {
        const user_t *user = &arr[i];
        printf("user[%lu]: id = %u, name = %s\n", i, user->id, user->name);
    }
    status = true;
    return status;
}
static bool write_users(size_t len, const user_t *arr) {
    bool status = true;
    if (!arr || len == 0) {
        return false;
    }

    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        const user_t *user = &arr[i];
        if (fprintf(fp, USER_FORMAT, user->id, user->name) < 0) {
            status = false;
            break;
        }
    }
    fflush(fp);
    fclose(fp);
    return status;
}
static bool read_users(size_t len, user_t *arr) {
    bool status = true;
    if (!arr || len == 0) {
        return false;
    }
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        return false;
    }

    size_t i = 0;
    while (i < len && fscanf(fp, USER_FORMAT, &arr[i].id, arr[i].name) != EOF) {
        i++;
    }

    fclose(fp);
    return status;
}
static bool update_user(uint32_t id, const char *name) {
    bool status = true;
    if (!name || id == 0) {
        return false;
    }

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        return false;
    }
    FILE *tmp = fopen(FILE_NAME ".tmp", "w");
    if (!tmp) {
        fclose(fp);
        return false;
    }

    user_t user = {0};
    while (fscanf(fp, USER_FORMAT, &user.id, user.name) != EOF) {
        if (user.id == 0 || user.name[0] == '\0') {
            continue;
        }

        if (user.id == id) {
            if (fprintf(tmp, USER_FORMAT, user.id, name) < 0) {
                status = false;
                break;
            }
        } else {
            if (fprintf(tmp, USER_FORMAT, user.id, user.name) < 0) {
                status = false;
                break;
            }
        }
    }
    long fppos = ftell(fp);
    long tmppos = ftell(tmp);
    fclose(tmp);
    fclose(fp);

    if (fppos != tmppos) {
        status = false;
        goto End;
    }

    if (remove(FILE_NAME) != 0) {
        status = false;
        goto End;
    }

    if (rename(FILE_NAME ".tmp", FILE_NAME) != 0) {
        status = false;
    }

End:
    return status;
}
