#include <stdlib.h>
#include <stdio.h>

struct date {
  short int year;
  unsigned char month, day;
};

struct record {
  struct date when;
  float minT, avgT, maxT, wind;
  unsigned char snow, prec;
};

void print(struct record r) {
  printf("%d-%d-%d %f %f %f %d %d %f\n",
          r.when.year, r.when.month, r.when.day,
          r.minT, r.avgT, r.maxT, r.snow, r.prec, r.wind);
}

int compare(struct date w, int y, int m , int d) {
  if (w.year != y)
    return w.year - y;
  if (w.month != m)
    return w.month - m;
  if (w.day != d)
    return w.day - d;
  return 0;
}

int main() {
  FILE * fin = fopen("waether.dat", "r");
  int y, m, d;
  int first, last;
  if (fin == NULL) {
    fprintf(stderr, "Cant open file\n");
    exit(1);
  }
  printf("Enter y m d: ");
  scanf("%d %d %d", &y, &m, &d);
  first = 0;
  fseek(fin, 0, SEEK_END);
  last = ftell(fin) / sizeof(struct record) - 1;
  while(1) {
    int middle = (first + last) / 2;
    struct record r;
    int c;
    printf("first=%d, middle=%d, last=%d\n", first, middle, last);
    fseek(fin, middle * sizeof(r), SEEK_SET); //need to read the right place
    fread(&r, sizeof(r), 1, fin);
    c = compare(r.when, y, m, d);
    if (c == 0) {
      printf("found it:\n");
      print(r);
      break;
    }
    else if (c < 0) {
      first = middle + 1;
    }
    else{
      last = middle - 1;
    }
  }

  fclose(fin);
}