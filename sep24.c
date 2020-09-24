#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct entry {
  char * uname, *pwd, *uid, *gid, *name, *dir, *shell;
};

struct vec {
  struct entry * * array;
  int num , cap;
};

struct vec * make_vec() {
  array = (struct entry * *) malloc(sizeof(struct entry *));
  cap = 1;
  num = 0;
}

void resize(struct vec * V) {
  V->cap *=2;
  if (V-> cap == 0)
    V->cap = 1;
  struct entry ** n = (struct entry **) malloc(V-> cap * sizeof(struct entry*));
  int i;
  for (i = 0; i < V->num;i++) {
    n[i] = V->array[i];
  }
}

void vec_add(struct vec * V, struct entry * E) {
  if (V->num >= cap)
    resize(V);
  V -> array[V->num] = E;
  V -> num++;
}

int main() {
  char line[1000];
  FILE * pwf = fopen("/etc/passwd", "r");
  while(1) {
    char * s = fgets(line, 999, pwf);
    if (s == NULL)
      break;
    char * uname, *pwd, *uid, *gid, *name, *dir, *shell;
    // kind of like substr strtok!!
    // need to do strdup because of the poinbters ins strtok
    struct entry * e = (struct entry *) malloc(sizeof(struct entry));
    e->uname = strdup(strtok(line, ":\n"));
    e->pwd = strdup(strtok(NULL, ":\n"));
    e->uid = strdup(strtok(NULL, ":\n"));
    e->gid = strdup(strtok(NULL, ":\n"));
    e->name = strdup(strtok(NULL, ":\n"));
    e->dir = strdup(strtok(NULL, ":\n"));
    e->shell = strdup(strtok(NULL, ":\n"));
    // you can print stuff here
  }
  fclose(pwf);
}