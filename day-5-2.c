#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct tuple {
  long n1;
  long n2;
};

int main() {
  int fd = open("day-5.input", O_RDONLY);
  struct stat st;
  fstat(fd, &st);

  size_t len = st.st_size;
  void *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  char *str = (char *) p;
  close(fd);

  int npos = 0;
  for (int i = 0; ; i++) {
    if (str[i] == '\0') break;
    if (str[i] == '\n' && str[i + 1] == '\n') npos = i;
  }

  str[npos] = '\0';
  char *nums = &str[npos + 2];
  char *saveptr1;
  char *saveptr2;
  char *rngscp = strdup(str);
  char *rngs = strtok_r(str, "\n", &saveptr1);
  char *pnums = strtok_r(nums, "\n", &saveptr2);

  char *saveptr3;
  rngscp = strtok_r(rngscp, "\n", &saveptr3);

  int tplen = 0;
  while (rngscp != NULL) {
    for (int i = 0; ; i++) {
      if (rngscp[i] == '\0') break;
      if (rngscp[i] == '-') tplen++; 
    }
    
    rngscp = strtok_r(NULL, "\n", &saveptr3);
  }

  struct tuple *tprngs = malloc(tplen * sizeof(struct tuple));
  char *saveptr4;
  int tploc = 0;
  while (rngs != NULL) {
    long n1 = strtol(strtok_r(rngs, "-", &saveptr4), NULL, 10);
    long n2 = strtol(strtok_r(NULL, "-", &saveptr4), NULL, 10);

    tprngs[tploc] = (struct tuple) {n1, n2};
    tploc++;

    rngs = strtok_r(NULL, "\n", &saveptr1);
  }

  long long fresh = 0;
  for (int j = 0; j < tplen; j++) {
    fresh += tprngs[j].n2 - tprngs[j].n1;
  }

  free(tprngs);
  printf("Fresh ingredients: %lld\n", fresh);

  return 0;
}
