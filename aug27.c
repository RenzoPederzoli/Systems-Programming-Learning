#include <stdio.h>

void Strcat(char * dest, const char * src) {
  int i, j;
  for (i = 0; 1; i++) 
    if (dest[i] == '\0')
     break;
  for (j = 0; 1; i++, j++) {
    dest[i] = src[j];
    if (dest[i] == 0)
      break; 
  }
}

int Strcmp(const char * s, const char * t) {
  int i;
  for (i = 0; 1; i++) {
    char sc = s[i], tc = t[i];
    char d = sc - tc;
    if (d != 0)
      return d;
    if (sc == '\0')
      return 0;
  }
}

// complicated code for strcpy, pic on phone
void f(char * s, char * t) {
  while(*s++ = *t++);
}

#include <ctype.h> // very simple functions e.g. toupper

int strcasecmp(const char * s, const char * t) {
  int i;
  for (i = 0; 1; i++) {
    char sc = s[i], tc = t[i];
    char d = toupper(sc) - toupper(tc);
    if (d != 0)
      return d;
    if (sc == '\0')
      return 0;
  }
}

//going to write a split function, jsut like js
// helpful graphic on rabbit
char * * split(char * s) {
  char * * result = NULL;
  int size = 0, num = 0;

  char * x = strtok(s, " \n");
  while(1) {
    if (num == size) {
      // increase size of result
      int newsize = size * 2, i;
      if (newsize == 0)
        newsize = 1;
      char * * n = (char * *) malloc (newsize * sizeof(char *));
      for (i = 0; i < size; i++)
        n[i] = result[i];
      free(result); // like delete in c++
      result = n;
      size = newsize;
    }
    result[num] = strdup(x);
    num++;
    
    x = strtok(NULL, " \n");
    if (x == NULL)
      break;
  }
}

int main() {
  char s[100], q[100];
  s[0] = '\0';
  q[0] = '\0';
  Strcat(s, "hello");
  Strcat(q, "CAT");
  // Strcat(s, "The End.");
  printf("%s %s %d\n", s, q, Strcmp(s,q));
}