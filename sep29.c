#include <stdio.h>

int main(int argc, char * argv[]) {
  printf("The command line was \n");
  int i;
  for (i=0; i < argc; i++) {
    printf("%d : \"%s\"\n", i , argv[i]);
  }
}