/*
Write a function int multiply(int a, int b) and describe how arguments are passed by value.
Then, extend it with a void saveResultToFile(int result) function that writes the value to a file named "output.txt".
Explain how file I/O works in C.
*/

#include <stdio.h>

static int multiply(int a, int b)
{
    return a * b;
}
static void saveSumToFile(int sum)
{
    FILE *fp = fopen("output.txt", "w");
    if (NULL == fp)
    {
        return;
    }
    fprintf(fp, "sum = %d", sum);
    fclose(fp);
}

int main(void)
{
    int a;
    int b;
    int sum;

    printf("Enter num for a and num for b.\n");
    scanf("%d, %d", &a, &b);

    sum = multiply(a, b);

    saveSumToFile(sum);

    return 0;
}
