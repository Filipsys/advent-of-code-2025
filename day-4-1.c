#include <stdio.h>
#include <string.h>

int main() {
  const char *odata = "..@@.@@@@.\n\
@@@.@.@.@@\n\
@@@@@.@.@@\n\
@.@@@@..@.\n\
@@.@@@@.@@\n\
.@@@@@@@.@\n\
.@.@.@.@@@\n\
@.@@@.@@@@\n\
.@@@@@@@@.\n\
@.@.@@@.@.";

  char data[strlen(odata) + 1];
  strcpy(data, odata);

  char *saveptr1;
  char *pl = strtok_r(data, "\n", &saveptr1);
  int llen = 0;
  if (pl != NULL) llen = strlen(pl);

  int gi = 0;
  int tt = 0;
  while (pl != NULL) {
    for (int i = 0; i < llen; i++) {
      if (pl[i] == '.') continue;

      for (int j = 0; j < 9; j++) {
        int st = 0;

        if (gi - (i - 1) > 0 && pl[i + (gi - (i - 1)) % llen]) st++;
        if (gi - (i - llen - 1) > 0) st++;
        if (gi - (i - llen) > 0) st++;
        if (gi - (i - llen + 1) > 0) st++;
        if (gi - (i + 1) > 0) st++;
        if (gi - (i + llen + 1) > 0) st++;
        if (gi - (i + llen) > 0) st++;
        if (gi - (i + llen - 1) > 0) st++;
        if (gi - (i - 1) > 0) st++;

        if (st < 4) tt++;
      }

      gi++;
    }

    pl = strtok_r(NULL, "\n", &saveptr1);
  }

  printf("Total acessible toilet paper: %i", tt);
  return 0;
}
