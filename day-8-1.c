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

struct connection {
  struct pair *p1;
  struct pair *p2;
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

struct position *parse(char *str, int collen) {
  char *saveptr1;
  char *pstr = strtok_r(strdup(str), "\n", &saveptr1);
  
  int pcount = 0;
  struct position *posarr = malloc(collen * sizeof(struct position));
  while (pstr != NULL) {
    char *saveptr2;
    // struct pair p;
    // p.n1 = (struct position) {
    //   strtol(strtok_r(pstr, ",", &saveptr2), NULL, 10),
    //   strtol(strtok_r(NULL, ",", &saveptr2), NULL, 10),
    //   strtol(strtok_r(NULL, ",", &saveptr2), NULL, 10),
    // };

    posarr[pcount] = (struct position) {
      strtol(strtok_r(pstr, ",", &saveptr2), NULL, 10),
      strtol(strtok_r(NULL, ",", &saveptr2), NULL, 10),
      strtol(strtok_r(NULL, ",", &saveptr2), NULL, 10),
    };

    // pstr = strtok_r(NULL, "\n", &saveptr1);

    // int cloop = 0;
    // int sdist;
    // struct position sdistp = (struct position) {0, 0, 0};
    // char *saveptr3;
    // char *strloop = strtok_r(strdup(str), "\n", &saveptr3);
    // while (strloop != NULL) {
    //   if (cloop == pcount) continue;

      // calcdist(p.n1, );

    //   cloop++;
    //   strloop = strtok_r(NULL, "\n", &saveptr3);
    // }
    //
    // char *saveptr4;
    // p.n2 = (struct position) {
    //   strtol(strtok_r(pstr, ",", &saveptr4), NULL, 10),
    //   strtol(strtok_r(NULL, ",", &saveptr4), NULL, 10),
    //   strtol(strtok_r(NULL, ",", &saveptr4), NULL, 10),
    // };

    // pairs[pcount] = p;
    pcount++;

    pstr = strtok_r(NULL, "\n", &saveptr1);
  }

  for (int i = 0; i < collen / 2; i++) {
    // printf("Pair: %d,%d,%d %d,%d,%d\n", pairs[i].n1.x, pairs[i].n1.y, pairs[i].n1.z, pairs[i].n2.x, pairs[i].n2.y, pairs[i].n2.z);
    printf("Position: %d,%d,%d\n", posarr[i].x, posarr[i].y, posarr[i].z);
  }
  
  return posarr;
}

int main() {
  char *input = readf();

  int collen = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == '\n') collen++;
  }

  struct position *posarr = parse(input, collen);
  struct pair *pairs = malloc(collen * sizeof(struct pair));

  for (int i = 0; i < collen; i++) {
    int dist = 2147483647;
    int min;

    for (int j = i + 1; j < collen; j++) {
      int newdist = calcdist(posarr[i], posarr[j]);

      if (newdist < dist) {
        dist = newdist;
        min = j;
      }
    }

    struct pair p;
    pairs[i].n1 = (struct position) {posarr[i].x, posarr[i].y, posarr[i].z};
    pairs[i].n2 = (struct position) {posarr[min].x, posarr[min].y, posarr[min].z};
  }

  for (int i = 0; i < collen; i++) {
    printf("Closest pair: %d,%d,%d to %d,%d,%d\n", pairs[i].n1.x, pairs[i].n1.y, pairs[i].n1.z, pairs[i].n2.x, pairs[i].n2.y, pairs[i].n2.z);
  }

  struct connection *conn = malloc(collen);
  int cc = 0;
  for (int i = 0; i < collen; i++) {
    for (int j = i + 1; j < collen; j++) {
      if (pairs[i].n1.x == pairs[j].n1.x &&
          pairs[i].n1.y == pairs[j].n1.y &&
          pairs[i].n1.z == pairs[j].n1.z) {
        conn[cc] = (struct connection) {&pairs[i], &pairs[j]};
        continue;
      }

      if (pairs[i].n2.x == pairs[j].n2.x &&
          pairs[i].n2.y == pairs[j].n2.y &&
          pairs[i].n2.z == pairs[j].n2.z) {
        conn[cc] = (struct connection) {&pairs[i], &pairs[j]};
        continue;
      }
    }
  }

  for (int i = 0; i < collen; i++) {
    printf("Pointer connection: %p - %p\n", conn[i].p1, conn[i].p2);
  }

  free(posarr);
  return 0;
}
