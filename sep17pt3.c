#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// THIS PROGRAM PIPES PROG 1 AND PROG 2
// for prog1 and prog2
// you need to call the .exe files 
// and not the .c file
int main() {
  int p, s, link[2];

  pipe(link);

  p = fork();
  if (p == 0) {
    close(1);
    dup(link[1]);
    execlp("prog1", "prog1", NULL);
    fprintf(stderr, "cant exec prog1\n");
    exit(1);
  }

  // this is here cause second process wasnt exiting
  close(link[1]);

  p = fork();
  if (p == 0) {
    close(0);
    dup(link[0]);
    execlp("prog2", "prog2", NULL);
    fprintf(stderr, "cant exec prog2\n");
    exit(1);
  }

  // wahts below tells you exit status 0 or 1
  p = wait(& s);
  if (WIFEXITED(s))
    printf("process %d exitted with status %d\n", p, WEXITSTATUS(s));

  p = wait(& s);
  if (WIFEXITED(s))
    printf("process %d exitted with status %d\n", p, WEXITSTATUS(s));

  printf("the main process is ending\n");
}