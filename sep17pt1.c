#include <stdio.h>
#include <stdlib.h>

// THIS IS PROG 1 GIVES RANDOM INTS
int main() {
  while(1) {
    int x = random() % 100 + 1;
    printf("%d", x);
  }
}