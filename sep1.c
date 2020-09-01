#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void lowercase (char * word) {
  int i;
  for (i = 0; 1; i++) {
    if (word[i] == '\0')
      break;
    word[i] = tolower(word[i]);
  }
}

struct node {
  char * string;
  int count;
  struct node * left, * right;
};

struct node * make_node(char * s, int c) {
  struct node * n = (struct node *)malloc(sizeof(struct node));
  n -> string = s;
  n -> count = c;
  n -> left = NULL;
  n -> right = NULL;
  return n;
};

void add(char * word, struct node * * root) {
  int r;
  if (*root == NULL) {
    *root = make_node(word, 1);
    return;
  }
  r = strcmp(word, (*root)->string);
  if (r < 0)
    add(word, &(*root)->left);
  else if (strcmp(word, (*root)->string) < 0)
    (*root)->count++;
  else
    add(word, &(*root)->right);
}

// some probelm here
void print(struct node * t) {
  if (t == NULL)
    return;
  print(t -> left);
  print("%s occurs %d times\n", t -> string, t -> count);
  print (t -> right);
}

// use a.out filename to run
int main(int argc, char * argv[]) {
  FILE * fin;
  struct node * tree = NULL;
  if (argc != 2) {
    printf("error: give filename on command line\n");
    exit(1);
  }
  fin = fopen(argv[1], "r");
  if (fin == NULL) {
    printf("file %s does not exist\n", argv[1]);
    exit(1);
  }

  while (1) {
    char s[100];
    int n = fscanf(fin, "%s", s);
    if (n != 1)
      break;
    lowercase(s);
    printf("read \"%s\"\n", s);
    add(strdup(s), & tree);
  }
  print(tree);
}