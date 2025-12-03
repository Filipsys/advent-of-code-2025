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

  int sum = 0;
  while (pch != NULL) {
    int n1 = 0;
    int n2 = 0;
    int depth = 0;

    for (int i = 0; ; i++) {
      if (pch[i + 1] == '\0') break;
      int charnum = pch[i] - '0';

      if (charnum > n1) {
        n1 = charnum;
        depth = i;
      }
    }

    printf("Highest first number: %d -- depth: %d\n", n1, depth);

    for (int i = depth + 1; ; i++) {
      if (pch[i] == '\0') break;
      int charnum = pch[i] - '0';

      if (charnum > n2) n2 = charnum;
    }

    printf("Highest second number: %d -- depth: %d\n", n1, depth);

    int nl = snprintf(NULL, 0, "%d%d", n1, n2);
    char *numstr = malloc(nl + 1);
    snprintf(numstr, nl + 1, "%d%d", n1, n2);
    sum += strtol(numstr, NULL, 10);

    pch = strtok_r(NULL, "\n", &saveptr1);
  }

  printf("Sum: %d\n", sum);

  return 0;
}
