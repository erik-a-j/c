// Evaluate the following program. What is the output of the program?
#include <stdio.h>
#include <stdint.h>
#define EXPRESSION (3 * j / k - 2)
#define SET_VARIABLES \
{ \
i = 3; \
j = 2; \
k = 0; \
}
int main(void)
{
    int i = 0, j = 7, k = 6;
    char a = 'A', b = '3';
    int32_t x, y = 3;
    uint32_t z = 32;
    double d;
    x = EXPRESSION; //x == 1;
    // 3 * j:7 / k:6 - 2 == 1;

    printf("A) %d\n", x); // "A) 1";

    y -= ((j << 1) & (k >> 1)); //y == 1;
    // (j:7 << 1) == 14; (k:6 >> 1) == 3; 14 & 3 == 2; y:3 - 2 == 1;

    printf("B) %d\n", y); // "B) 1";

    x = (!(i && k) || !k) ? k + b : j + b; //x == 57;
    // !(i:0:FALSE:0 && k:6:TRUE:1) == TRUE:1; !k:6:TRUE:1 == FALSE:0; TRUE:1 || FALSE:0 == TRUE:1;
    // k:6 + b:'3':51 == 57;

    printf("C) %d\n", x); // "C) 57";

    a += (b + k--) % 10; //a == 72; k == 5;
    // b:'3':51 + k--:6 == 57; 57 % 10 == 7; a:'A':65 + 7 == 72;

    printf("D) %d\n", a); // "D) 72";

    d = (double)j * 100 / --k / 3; //d == 58.333333 //k == 4;
    // (double)j:7.0 * 100 == 700.0;
    // 700.0 / --k:4 == 175.0;
    // 175.0 / 3 == 58.333333;

    printf("E) %f\n", d); // "E) 58.333333";

    x = -1;
    y = (x < z) ? (k < j < 0) : (b >= a < i); //y == 0;
    // x:-1 < z:32 == TRUE;
    // k:4 < j:7 < 0 == FALSE:0;

    printf("F) %d\n", y); // "F) 0";

    d = x / z; //d == 134217727.000000;
    // (uint32_t)x:-1 == UINT32_MAX;
    // (uint32_t)x:UINT32_MAX / z:32 == 134217727;

    printf("G) %f\n", d); // "G) -0.031250";

    i = 4;
    j = -1;
    k = 0;
    x = i && j && k; //x == 0;
    // i:4:TRUE && j:-1:TRUE && k:0:FALSE == FALSE:0;

    y = i || j && k; //y == 1;
    // i:4:TRUE || j:-1:TRUE && k:0:FALSE == TRUE:1;

    printf("H) %d, %d\n", x, y); // "H) 0, 1";

    x = i && j || k; //x == 1;
    // i:4:TRUE && j:-1:TRUE || k:0:FALSE == TRUE:1;

    y = i || j || k; //y == 1;
    // i:4:TRUE || j:-1:TRUE || k:0:FALSE == TRUE:1;

    printf("I) %d, %d\n", x, y); // "I) 1, 1";

    SET_VARIABLES;
    //i == 3;
    //j == 2;
    //k == 0;

    y = ++i || ++j && k++; //y == 1; i == 4; j == 2; k == 0;
    // ++i:4:TRUE || ++j:3:TRUE && k++:0:FALSE == TRUE:1;

    printf("J) %d, %d, %d, %d\n", i, j, k, y); // "J) 4, 2, 0, 1";

    SET_VARIABLES;
    //i == 3;
    //j == 2;
    //k == 0;

    y = (123 && --i) ? k++ : ++k; //y == 0; k == 1;
    // 123 && --i:2 == TRUE;
    // k++ = 0;

    printf("K) %d, %d, %d, %d\n", i, j, k, y); // "K) 2, 2, 1, 0";

    SET_VARIABLES;
    //i == 3;
    //j == 2;
    //k == 0;

    y = ++i && ++j && k++; //y == 0; k == 1;
    // ++i:4 && ++j:3 && k++:0 == FALSE:0;

    printf("L) %d, %d, %d, %d\n", i, j, k, y); // "L) 4, 3, 1, 0";

    i = 4;
    j = --i; //j == 3; i == 3;
    k = i--; //k == 3; i == 2;
    printf("M) %d, %d, %d\n", i, j, k); // "M) 2, 3, 3";

    i = -1; //i == -1;
    j = 1;  //j == 1;

    i&& printf("N) Hello World!\n") && --j; // "N) Hello World!\n"; j == 0;
    // i:-1:TRUE;
    // printf("N) Hello World!\n") == 16:TRUE;
    // --j:0;

    ++i && j && printf("O) Hello World!\n"); //i == 0;
    // ++i:0:FALSE;

    i || printf("P) Hello World!\n") || j++; // "P) Hello World!\n";
    // i:0:FALSE;
    // printf("P) Hello World!\n") == 16:TRUE;

    j-- || !printf("Q) Hello World!\n") || i++; //j == -1; i == 1;
    // j--:0:FALSE
    // !printf("Q) Hello World!\n") == !(16):FALSE;
    // i++:0:FALSE

    printf("R) %d, %d\n", i, j); // "R) 1, -1\n"
    return 0;
}