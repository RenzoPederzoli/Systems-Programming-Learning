#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
//#include <unistd.h>

struct node {
  char * string;
  struct node * left, * right;
};

struct node * make_node(char * s) {
  struct node * n = (struct node *)malloc(sizeof(struct node));
  n -> string = s;
  n -> left = NULL;
  n -> right = NULL;
  return n;
};

void add(char * word, struct node * * root) {
  int r;
  if (*root == NULL) {
    *root = make_node(word);
    return;
  }
  r = strcmp(word, (*root)->string);
  if (r < 0)
    add(word, &(*root)->left);
  else
    add(word, &(*root)->right);
}

void print(struct node * t) {
  if (t == NULL)
    return;
  print(t -> left);
  printf("%s \n", t -> string);

  print(t -> right);
}

// missing something here
void tree_out(struct node * t, int file) {
  char newline = '\n';
  if (t == NULL)
    return;
  tree_out(t -> left, file);
  write(file, t-> string, strlen(t -> string));
  write(file, & newline, 1);
  tree_out(t -> right, file);
}

char * random_string() {
  int i, len = rand() % 8 + 3;
  char * str = (char *)malloc(len+1);
  for (i = 0; i < len; i++) {
    str[i] = rand() % 26 + 'a';
  }
  str[len] = '\0';
  return str;
}

void shuffle(char * * A, int N) {
  int i;
  for (i = 0; i < 2*N; i++) {
    int pos = random() % N;
    char * a = A[0];
    A[0] = A[pos];
    A[pos] = a;
  }
}

int main(int argc, char * argv[]) {
  struct node * T = NULL, * U = NULL;
  int p, i, numstrs, link1[2];
  FILE * pipein;
  if (argc != 2) {
    fprintf(stderr, "usage: %s numstrings\n", argv[0]);
    exit(1);
  }
  srandomdev();
  numstrs = atoi(argv[1]);
  char * * array = (char * *)malloc(numstrs * sizeof(char *));
  for (i = 0; i < numstrs; i++) {
    array[i] = random_string();
  }
  for(i = 0; i < numstrs; i++) {
    add(array[i], &T);
  }
  shuffle(array, numstrs);
  for(i = 0; i < numstrs; i++) {
    add(array[i], &U);
  }
  // does a bunch of print stuff here to see both proceses at work
  print(T);

  pipe(link1);
  p = fork();
  if (p == 0) {
    tree_out(T, link1[0]);
    close(link1[1]);
    exit(0);
  }

  pipein = fdopen(link1[0], "r");
  for(i = 0; 1; i++) {
    char s[100];
    int n = fscanf(pipein, "%s", s);
    if (n <= 0)
      break;
    printf("read somwething");
  }
}
  