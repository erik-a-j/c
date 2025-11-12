/*
You are given this flowchart:

Start → Input x, y
If x > y → Print “X greater” → End
Else → Print “Y greater or equal” → End

Write equivalent C code and describe how conditionals are represented in flowcharts versus in C.
*/

#include <stdio.h>

int a;

int main(void)
{
    int x;
    int y;
    printf("Enter num for x and num for y.\n");
    scanf("%d, %d", &x, &y);

    if (x > y)
    {
        printf("X greater\n");
    }
    else
    {
        printf("Y greater or equal\n");
    }

    return 0;
}