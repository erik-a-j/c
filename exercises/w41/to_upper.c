#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define is_lower(ch) ((ch) >= 'a' && (ch) <= 'z')
#define is_upper(ch) ((ch) >= 'A' && (ch) <= 'Z')
#define to_upper(ch) ((ch) - ('a' - 'A'))

int main(void) {
  char ch_upper = '\0';
  char ch = '\0';
  int assigned = 0;
  while (assigned == 0) {
    printf("Enter lowercase char: ");
    assigned = scanf("%c", &ch);
    if (assigned == EOF) {
      printf("error\n");
      return -1;
    }
    if (ch == '\n') {
      assigned = 0;
      printf("\x1b[1A\x1b[K");
    }
  }
  if (!is_lower(ch)) {
    printf("char: %c is not lowercase\n", ch);
  }
  else {
    printf("uppercase char: %c\n", to_upper(ch));
  }

  srand(time(NULL));

  int rnum1 = rand();
  int rnum2 = rand();

  printf("random 1: \x1b[1m" "%d" "\x1b[m\n", rnum1 % 100 + 1);
  printf("random 2: \x1b[1m" "%d" "\x1b[m\n", rnum2 % 100 + 1);

}