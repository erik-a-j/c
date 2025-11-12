/*
Convert the following pseudocode into a working C program:
Start
  Input n
  Set sum = 0
  For i = 1 to n
    sum = sum + i*i
  Print sum
End
*/
#include <stdio.h>

int main(void)
{ //Start
    int sum = 0;
    int n = 0;
    int i = 0;

    printf("choose a number.\n");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        sum = sum + i * i;
    }
    printf("sum = %d\n", sum);

    return 0;
} //End