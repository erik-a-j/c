#include <stdio.h>

#if !defined(NUMBER) || (NUMBER != 8 && NUMBER != 16)
#error ERROR
#endif

int main(void) {
  printf("%d\n", NUMBER);
  return 0;
}