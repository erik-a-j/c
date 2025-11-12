/*
Write a program that simulates a simple temperature converter (Celsius ↔ Fahrenheit).
Show modular design by using two functions:
*/
#include <stdio.h>

static float toCelsius(float f)
{
    return (f - 32.0f) * 5.0f / 9;
}
static float toFahrenheit(float c)
{
    return (c * 9.0f / 5) + 32.0f;
}

int main(void)
{
    float degrees;
    char CorF;
    printf("Enter [degrees] [C|F]: ");
    if (EOF == scanf("%f %c", &degrees, &CorF))
    {
        return 1;
    }

    if ('C' == CorF)
    {
        float toF = toFahrenheit(degrees);
        printf("%f°C == %f°F\n", degrees, toF);
    }
    else if ('F' == CorF)
    {
        float toC = toCelsius(degrees);
        printf("%f°F == %f°C\n", degrees, toC);
    }
    else
    {
        printf("FAIL!!!\n");
    }

    return 0;
}