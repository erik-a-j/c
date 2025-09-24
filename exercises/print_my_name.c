#include <stdio.h>

#ifndef MY_NAME
#define MY_NAME EMPTY
#endif

#define X(x) #x
#define STRINGIFY(x) X(x) 

int main(void) {
  printf(STRINGIFY(MY_NAME)"\n");
  return 0;
}