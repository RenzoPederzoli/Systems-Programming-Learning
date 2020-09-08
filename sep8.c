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

int main() {
  FILE * fin = fopen("/home/www/class/een322/weather.txt", "r");
  FILE * fout = fopen("weather.dat", "w");
  if (fin == NULL || fout == NULL) {
    fprintf(stderr, "Cant open file\n");
    exit(1);
  }
  while(1) {
    struct record r;
    int x = fscanf(fin,"%hd %hhd %hhd %f %f %f %hhd %hhd %f",
                    &r.when.year, &r.when.month, &r.when.day,
                    &r.minT,&r.avgT,&r.maxT,
                    &r.snow,&r.prec, &r.wind);
    if (x != 9)
      break;
    fwrite(&r, sizeof(r), 1, fout);
  }
  fclose(fin);
  fclose(fout);
}