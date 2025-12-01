#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  // Read the damn file
  int fd = open("day-1.input", O_RDONLY);
  struct stat st;
  fstat(fd, &st);

  size_t len = st.st_size;
  void *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  char *str = (char *) p;

  close(fd);

  // Finally do some work on it
  char *pch = strtok(str, "\n");

  int hitCount = 0;
  int currentAngle = 50;

  while (pch != NULL) {
    signed char dir = *pch == 'L' ? -1 : 1; 
    int angle = atoi(pch + 1);

    currentAngle = (currentAngle + angle * dir) % 100;
    if (currentAngle < 0) currentAngle += 100;
    if (currentAngle == 0) hitCount++;

    pch = strtok(NULL, "\n");
  }

  munmap(p, len);
  printf("Zero hit count: %d\n", hitCount);

  return 0;
}
