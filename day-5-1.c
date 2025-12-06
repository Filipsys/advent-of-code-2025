#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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
    printf("%02X ", str[i]);
    if (str[i] == '\0') break;
    if (str[i] == '\n' && str[i + 1] == '\n') npos = i;
  }

  str[npos] = '\0';
  char *nums = &str[npos + 2];
  char *saveptr1;
  char *saveptr2;
  // char *rngs = strtok_r(str, "\n", &saveptr1);
  char *pnums = strtok_r(nums, "\n", &saveptr2);

  for (int i = 0; ; i++) {
    if (str[i] == '\0') break;
  }
  // printf("RNGS\n%s\nNUMS\n%s", str, nums);

  while (pnums != NULL) {
    for (int j = 0; ; j++) {
      // if (rngs[j] == '\0') break;

      // printf("%s\n", rngs);
      // int start = strtol(strtok(rngs[j], "-"), NULL, 10);
      // int end = strtol(strtok(NULL, "-"), NULL, 10);

      // printf("Start: %d, end: %d", start, end);

  //     rngs = strtok_r(NULL, "\n", &saveptr2);
    }
  
    nums = strtok_r(NULL, "\n", &saveptr1);
  }

  return 0;
}
