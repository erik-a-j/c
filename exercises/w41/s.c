#include <stdio.h>
#include <stdint.h>

typedef struct f {
  unsigned char a : 1;
  unsigned char b : 1;
  unsigned char c : 1;
  unsigned char d : 1;
  unsigned char e : 1;
  unsigned char f : 1;
  unsigned char g : 1;
  unsigned char h : 1;
} f;

int main() {
  f a = {0};
  unsigned char *pa = (unsigned char*)&a;
  *pa = 1 << 1;

  printf("%d,%d,%d,%d,%d,%d,%d,%d\n", a.a, a.b, a.c, a.d, a.e, a.f, a.g, a.h);
}