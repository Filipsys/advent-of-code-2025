#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd = open("day-2.input", O_RDONLY);
  struct stat st;
  fstat(fd, &st);

  size_t len = st.st_size;
  void *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  char *str = (char *) p;

  close(fd);

  char *saveptr1;
  char *saveptr2;
  char *pch = strtok_r(str, ",", &saveptr1);

  unsigned long long int sum = 0;
  while (pch != NULL) {
    char *pnums = strtok_r(pch, "-", &saveptr2);
    unsigned long long int fnum = strtoull(pnums, NULL, 10);

    pnums = strtok_r(NULL, "-", &saveptr2);
    unsigned long long int snum = strtoull(pnums, NULL, 10);

    for (int i = fnum; i <= snum; i++) {
      int strlength = snprintf(NULL, 0, "%d", i);
      int halflen = strlength / 2;

      char *strnum = malloc(strlength + 1);
      snprintf(strnum, strlength + 1, "%d", i);
      strnum[strlength] = '\0';

      if (strlength % 2 != 0) {
        printf("Number length is odd: %d, new number: ", i);
        for (int j = halflen; j < strlength; j++) {
          strnum[j] = strnum[j + 1];
        }
        printf("%s\n", strnum);
      }

      char *fpart = malloc(halflen + 1);
      strncpy(fpart, strnum, halflen);
      fpart[halflen] = '\0';
      
      char *spart = malloc(halflen + 1);
      strncpy(spart, strnum + halflen, halflen);
      spart[halflen] = '\0';

      if (strcmp(fpart, spart) == 0) sum += i;

      free(strnum);
      free(fpart);
      free(spart);
    }

    pch = strtok_r(NULL, ",", &saveptr1);
  }

  munmap(p, len);
  printf("Sum: %llu\n", sum);

  return 0;
}
