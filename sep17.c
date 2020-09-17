#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include <fcntl.h>


// THIS IS EXAMPLE PROGRAM FOR FORK
int main() {
  int p, f;

  p = fork();
  if (p == 0) {
    // open will take over file descriptor 1
    close(1);
    // remember how to determine prot value
    f = open("output.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    execlp("ls", "ls", "-l", NULL);
    fprintf(stderr, "can't execlp ls\n");
    exit(1);
  }
  printf("I am the main process running\n");
}