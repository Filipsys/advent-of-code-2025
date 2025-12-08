#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

char *readFile() {
  int fd = open("day-6.input", O_RDONLY);
  struct stat st;
  fstat(fd, &st);

  size_t len = st.st_size;
  void *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  char *str = (char *) p;
  close(fd);

  return str;
}

char *parse(char *str) {
  char *saveptr;
  char *pstr = strtok_r(strdup(str), "\n", &saveptr);

  char *saveptr2;
  char *pstrcp = strtok_r(strdup(pstr), " ", &saveptr2);
  size_t rowlen = 0;
  while (pstrcp != NULL) {
    rowlen++;
    pstrcp = strtok_r(NULL, " ", &saveptr2);
  }

  char *saveptr3;
  char *pstrcp2 = strtok_r(strdup(str), "\n", &saveptr3);
  size_t collen = 0;
  while (pstrcp2 != NULL) {
    collen++;
    pstrcp2 = strtok_r(NULL, "\n", &saveptr3);
  }
  if (collen != 0) collen--;

  int **arr = malloc(rowlen * sizeof(int*));
  for (int i = 0; i < rowlen; i++) {
    arr[i] = malloc(collen * sizeof(int));
  }
  char *opchars = malloc(rowlen + 1);
  opchars[rowlen] = '\0';

  int ccol = 0;
  while (pstr != NULL) {
    char *saveptr3;
    char *strnums = strtok_r(strdup(pstr), " ", &saveptr3);

    int c = 0;
    while (strnums != NULL) {
      if (c > rowlen) c = 0;

      if (ccol < collen) {
        arr[c][ccol] = strtol(strnums, NULL, 10);
      } else {
        opchars[c] = strnums[0];
      }
      c++;

      strnums = strtok_r(NULL, " ", &saveptr3);
    }
    
    ccol++;
    pstr = strtok_r(NULL, "\n", &saveptr);
  }

  long long sum = 0;
  for (int i = 0; i < rowlen; i++) {
    long res = arr[i][0];
    for (int j = 1; j < collen; j++) {
      switch (opchars[i]) {
        case '+': res += arr[i][j]; break;
        case '-': res -= arr[i][j]; break;
        case '*': res *= arr[i][j]; break;
        case '/': res /= arr[i][j]; break;
      }
    }

    sum += res;
  }

  for (int i = 0; i < rowlen; i++) free(arr[i]);
  free(arr);
  free(opchars);

  printf("Sum: %lld\n", sum);
  
  return str;
}

int main() {
  char *input = readFile();
  char *parsed = parse(input);

  return 0;
}
