#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fd = open("day-3.input", O_RDONLY);
  struct stat st;
  fstat(fd, &st);

  size_t fl = st.st_size;
  void *p = mmap(NULL, fl, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  char *str = (char *) p;

  close(fd);

  char *saveptr1;
  char *pch = strtok_r(str, "\n", &saveptr1);

  // Get the battery length
  int blen = 0;
  for (int i = 0; pch[i] != '\0'; i++) blen++;

  unsigned long long int sum = 0;
  while (pch != NULL) {
    int highnums[12]; // 12 is the battery amount
    int depth = 0;
    int limit = 12 - 1; // 12 batteries - 1 for the first one

    for (int i = 0; i < 12; i++) {
      int loophigh = 0;

      for (int j = depth; ; j++) {
        if (j == blen - limit) break;
        int charnum = pch[j] - '0';

        if (charnum > loophigh) {
          loophigh = charnum;
          depth = j + 1;
        }
      }

      highnums[i] = loophigh;
      limit--;
    }

    // Sum up the joltage
    char jsum[blen + 1];
    for (int i = 0; i < blen; i++) jsum[i] = '0' + highnums[i];
    jsum[blen] = '\0';
    sum += strtoull(jsum, NULL, 10);

    pch = strtok_r(NULL, "\n", &saveptr1);
  }

  printf("Sum: %llu\n", sum);

  return 0;
}
