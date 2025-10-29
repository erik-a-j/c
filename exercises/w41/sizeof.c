#include <stdio.h>
#include <limits.h>
#include <float.h>
/*
Make a program using the printf function in stdio.h,
the sizeof operator and the min/max values defined in limits.h and float.h to display

  Size, min and max values of
  char, signed char and unsigned char.
  int, unsigned int, short int, unsigned short int,
  signed long int, unsigned long int, signed long long int and usigned long long int.
  float, double and long double.
  Size of enum color { RED, GREEN, BLUE, YELLOW, WHITE, BLACK };
*/
#define C1 "\e[1;38;5;220m"
#define C2 "\e[1;38;5;196m"
#define C3 "\e[1;38;5;46m"
#define RESET "\e[0m"

#define pti(type, size_spec, min, max) do { \
printf("%24s", #type": "); \
printf(C1"%zu"RESET"B, ", sizeof(type)); \
printf("range("C2 size_spec RESET","C3 size_spec RESET")\n", min, max); \
} while (0)

enum color { RED, GREEN, BLUE, YELLOW, WHITE, BLACK };

int main(void) {
  pti(char, "%hhd", CHAR_MIN, CHAR_MAX);
  pti(signed char, "%hhd", SCHAR_MIN, SCHAR_MAX);
  pti(unsigned char, "%hhu", 0, UCHAR_MAX);
  pti(int, "%d", INT_MIN, INT_MAX);
  pti(unsigned int, "%u", 0, UINT_MAX);
  pti(short int, "%hd", SHRT_MIN, SHRT_MAX);
  pti(unsigned short int, "%hu", 0, USHRT_MAX);
  pti(signed long int, "%ld", LONG_MIN, LONG_MAX);
  pti(unsigned long int, "%lu", (unsigned long int)0, ULONG_MAX);
  pti(signed long long int, "%lld", LLONG_MIN, LLONG_MAX);
  pti(unsigned long long int, "%llu", (unsigned long long int)0, ULLONG_MAX);
  pti(float, "%e", FLT_MIN, FLT_MAX);
  pti(double, "%e", DBL_MIN, DBL_MAX);
  pti(long double, "%Le", LDBL_MIN, LDBL_MAX);
  pti(enum color, "%d", INT_MIN, INT_MAX);
}