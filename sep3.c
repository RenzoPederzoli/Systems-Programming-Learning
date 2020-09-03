#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// this includes unix functions which arent here
int main() {
  int inf;
  inf = open("pp.txt", O_RDONLY);
  if (inf < 0) {
    perror("open");
    exit(1);
  }
  while(1) {
    char c[1024];
    r = read(inf, c, 1024);
    if (r < 0) {
      perror("read");
      exit(1);
    }
    if (r == 0)
      break;
    r = write(1, c, r); // use r here because you only want to write what you succesfullt read
    if (r < 0) {
      perror("write");
      exit(1);
    }
  }
  close(inf);
}