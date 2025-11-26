/*
Study the behaviour of the strtok function in string.h; http://www.cplusplus.com/reference/cstring/strtok/
Make a stand-alone and self-contained function like strtok to split a string using a delimiter which is one character.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *split_string(const char *str, const char delim)
{
    static const char *pstr = NULL;
    static char *result = NULL;

    if (NULL != str)
    {
        size_t needed_size = strlen(str) + 1;
        if (NULL != result)
        {
            free(result);
        }
        result = malloc(needed_size);
        pstr = str;
    }

    if (NULL != result)
    {
        char *presult = result;
        while (('\0' != *pstr) && (delim != *pstr))
        {
            *presult++ = *pstr++;
        }
        *presult = '\0';

        while (delim == *pstr)
        {
            pstr++;
        }
        if (0 == strlen(result))
        {
            free(result);
            result = NULL;
            pstr = NULL;
        }
    }

    return result;
}

int main(void)
{
    const char *str = getenv("PATH");
    const char delim = ':';

    char *token = split_string(str, delim);
    while (NULL != token)
    {
        printf("%s\n", token);
        token = split_string(NULL, delim);
    }

    return 0;
}