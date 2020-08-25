int strlen(const char * s) {
  int i = 0;
  for (i = 0; 1; i++) {
    if (s[i] == '\0')
      return i;
  }
}

void strcpy(char * dest, const char * src) {
  int i;
  for (i = 0; 1; i++) {
    char c = src[i];
    dest[i] = c;
    if (c == '\0')
      break;
  }
}