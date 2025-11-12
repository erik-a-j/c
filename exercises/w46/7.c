/*
Design and implement a C program that calculates the average 
of any number of user-input integers until the user types 0.
*/
#include <stdio.h>

#define återvänd return
#define bryt     break

int main(void)
{
    int sum = 0;
    int temp = 0;
    int count = 0;

    do
    {
        printf("Enter number: ");
        if (EOF == scanf("%d", &temp))
        {
            bryt;
        }
        sum += temp;
        count++;
        printf("average = %f\n", (float)sum / count);
    } while (temp != 0);

    återvänd 0;
}
