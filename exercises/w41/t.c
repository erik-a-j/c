#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  struct termios raw = t;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  write(STDOUT_FILENO, "\x1b[1049h", 7);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

  int nread;
  char c[8];
  while ((nread = read(STDIN_FILENO, &c, 8)) != -1) {
    if (nread == 0) continue;
    write(STDOUT_FILENO, "\x1b[2J\x1b[H", 7);
    for (int i = 0; i < nread; i++) {
      printf("c[%d]: %c,%d\r\n", i, c[i], (int)c[i]);
    }
    if (c[0] == 'q') break;
  }

  write(STDOUT_FILENO, "\x1b[1049l", 7);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
}