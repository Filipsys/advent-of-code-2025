#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct position {
  int x;
  int y;
  int z;
};

struct pair {
  struct position n1;
  struct position n2;
  int dist;
};

int calcdist(struct position p1, struct position p2) {
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

char *readf() {
  int fd = open("day-8.input", O_RDONLY);
  struct stat st;
  fstat(fd, &st);

  void *p = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  char *str = (char *) p;
  close(fd);

  return str;
}

char *parse(char *str) {
  char *saveptr1;
  char *pstr = strtok_r(strdup(str), "\n", &saveptr1);

  int collen = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '\n') collen++;
  }
  printf("Columns length: %d\n", collen);
  
  int pcount = 0;
  struct pair *pairs = malloc(collen * sizeof(struct pair));
  while (pstr != NULL) {
    char *saveptr2;
    struct pair p;
    p.n1 = (struct position) {
      strtol(strtok_r(pstr, ",", &saveptr2), NULL, 10),
      strtol(strtok_r(NULL, ",", &saveptr2), NULL, 10),
      strtol(strtok_r(NULL, ",", &saveptr2), NULL, 10),
    };

    // pstr = strtok_r(NULL, "\n", &saveptr1);

    int cloop = 0;
    int sdist;
    struct position sdistp = (struct position) {0, 0, 0};
    char *saveptr3;
    char *strloop = strtok_r(strdup(str), "\n", &saveptr3);
    while (strloop != NULL) {
      if (cloop == pcount) continue;

      // calcdist(p.n1, );

      cloop++;
      strloop = strtok_r(NULL, "\n", &saveptr3);
    }

    char *saveptr4;
    p.n2 = (struct position) {
      strtol(strtok_r(pstr, ",", &saveptr4), NULL, 10),
      strtol(strtok_r(NULL, ",", &saveptr4), NULL, 10),
      strtol(strtok_r(NULL, ",", &saveptr4), NULL, 10),
    };

    pairs[pcount] = p;
    pcount++;

    pstr = strtok_r(NULL, "\n", &saveptr1);
  }

  for (int i = 0; i < collen / 2; i++) {
    printf("Pair: %d,%d,%d %d,%d,%d\n", pairs[i].n1.x, pairs[i].n1.y, pairs[i].n1.z, pairs[i].n2.x, pairs[i].n2.y, pairs[i].n2.z);
  }
  
  return "123";
}

int main() {
  char *input = readf();
  parse(input);
  
  return 0;
}
