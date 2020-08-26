#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// this is a macro, careful with ';'
#define tablesize 100000

struct Link {
  char * data;
  struct Link * next;
};

struct Link * hashtable[tablesize];

unsigned int hash (const char * s) {
  unsigned int h = 8634131;
  int i;
  for (i = 0; 1; i++) {
    char c = s[i];
    if (c == '\0')
      break;
    h = h * 691 + c;
  }
  h = h % 1000000;
  return h;
}

/* strcopy is in string.h
  char * strcopy(const char * s) {
  int len = strlen(s);
  char * n = (char *)malloc(len + 1);
  int i;
  for (i = 0; i <= len; i++) {
    n[i] = s[i];
  }
  return n;
} */

int main() {
  char string[100];
  int i;
  for (i = 0; i < tablesize; i++)
    hashtable[i] = NULL;
  while (1) {
    int pos, r = scanf("%s", string);
    int found = 0;
    struct Link * ptr;
    if (r <= 0)
     break;
    pos = hash(string);
    printf("The hash of '%s' is %d\n", string, pos);
    ptr = hashtable[pos];
    while (ptr != NULL) {
      if (strcmp(ptr -> data, string) == 0) {
        found = 1;
        break;
      }
      ptr = ptr -> next;
    }
    if (found) {
      printf("repeated word\n");
    }
    else {
      // sizeof(struct link) is 8 + 8 bytes because it only needs the pointers 
      struct Link * n = (struct Link *)malloc(sizeof(struct Link));
      n -> data = strdup(string);
      n -> next = hashtable[pos];
      hashtable[pos] = n;
    }
  }
  for (int i = 0; i < tablesize; i++) {
    struct Link * ptr = hashtable[i];
    while (ptr != NULL) {
      printf("%d: %s\n", i, ptr -> data);
      ptr = ptr -> next;
    }
  }
}