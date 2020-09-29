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
  struct vec * v = (struct vec*)malloc(sizeof(struct vec));
  v->array = (struct entry * *) malloc(sizeof(struct entry *));
  v->cap = 1;
  v->num = 0;
  return v;
}

int getsize(struct vec * v) {
  return v -> num;
}

struct entry * get(struct vec * v, int i) {
  if (i < 0 || i >= v->getsize(v)) {
    fprintf(stderr,"Index ot of bounds\n");
    exit(1);
  }
  return v->array[i];
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
  free(V-> array);
  V->array = n;
}

void vec_add(struct vec * V, struct entry * E) {
  if (V->num >= V->cap)
    resize(V);
  V -> array[V->num] = E;
  V -> num++;
}

int main() {
  struct vec * all = make_vec();
  char line[1000];
  FILE * pwf = fopen("/etc/passwd", "r");
  char * s = fgets(line, 999, pwf); // ignores first line
  while(1) {
    char * s = fgets(line, 999, pwf);
    if (s == NULL)
      break;
    // kind of like substr: strtok!!
    // need to do strdup because of the pointers in strtok (look at docs)
    struct entry * e = (struct entry *) malloc(sizeof(struct entry));
    char * uname = strtok(line, ":\n");
    if (uname == NULL)
      continue; // need to do this for white spaces in file since strtok might return NULL if no token is found, for all of them
    e->uname = strdup(uname);
    e->pwd = strdup(strtok(NULL, ":\n"));
    e->uid = strdup(strtok(NULL, ":\n"));
    e->gid = strdup(strtok(NULL, ":\n"));
    e->name = strdup(strtok(NULL, ":\n"));
    e->dir = strdup(strtok(NULL, ":\n"));
    e->shell = strdup(strtok(NULL, ":\n"));
    vec_add(all, e);
    // you can print stuff here
  }
  fclose(pwf);
  int i;
  for (i = 0; i < getsize(all); i++) {
    struct entry * e = get(all,i);
    printf("%s %s uses %s\n", e->uid, e->uname, e->shell);
  }
}