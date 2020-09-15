#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>

// writing ls -l
// some code from today in sep10.c file
int main() {
  // included some type of ignore 
  // there was somehting at beginiing
  int p, link1[2];
  
  pipe(link1);
  p = fork();
  if (p == 0) {
    close(1);
    dup(link1[1]); // replaces stdout
    execlp("ls", "ls", "-l", NULL);
    fprintf(stderr, "Can't execlp ls\n");
    exit(1);
  }

  // problem with the reading format
  FILE * fin = fdopen(link1[0], "r");
  while(1) {
    char prot[20], owner[20], group[20], month[10], timeyr[20], day[10], name[100];
    int refcount, size;
    int n = fscanf(fin, "%s %d %s %d %d %s %s %s %s", prot, &refcount, owner, group, &size, month, day, year, time, name);
    if (n <= 0)
      break;
    printf("%s has length %d\n", name, size);
  }
}