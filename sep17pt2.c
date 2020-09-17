#include <stdio.h>
#include <stdlib.h>

// THIS IS PROG 2 CALUCULTES AVG FROM NUMS
int main() {
  int total = 0, n = 0;
  while(1) {
    int x;
    scanf("%d", & x);
    n += 1;
    total += x;
    printf("average is %d", total/n)
  }
}