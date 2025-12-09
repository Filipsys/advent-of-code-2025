#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

char *readf() {
  int fd = open("day-7.input", O_RDONLY);
  struct stat st;
  fstat(fd, &st);

  void *p = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  char *str = (char *) p;
  close(fd);

  return str;
}

void *parse(char *str) {
  char *saveptr1;
  char *pstr = strtok_r(str, "\n", &saveptr1);

  int spos, rowlen;
  char *pstrcp = strdup(pstr);
  for (int i = 0; ; i++) {
    if (pstr[i] == '\0') {
      rowlen = i;
      break;
    }

    if (pstr[i] == 'S') spos = i;
  }

  int c = 0;
  int beams[rowlen];
  int prevbeams[rowlen];
  for (int i = 0; i < rowlen; i++) {
    beams[i] = prevbeams[i] = 0;
  }
  beams[spos] = 1;

  while (pstr != NULL) {
    for (int i = 0; i < rowlen; i++) {
      prevbeams[i] = beams[i];
    }

    for (int i = 0; ; i++) {
      if (pstr[i] == '\0') break;
      if (pstr[i] != '^') continue;
      if (prevbeams[i] == 1) c++; 

      beams[i - 1] = 1;
      beams[i + 1] = 1;
      beams[i] = 0;
    }

    pstr = strtok_r(NULL, "\n", &saveptr1);
  }

  printf("Count: %d\n", c);
  return 0;
}

int main() {
  char *input = readf();
  parse(input);

  return 0;
}
