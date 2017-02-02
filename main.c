#include "findpattern.h"
#include <stdio.h>

int main() {
  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));
  unsigned char * test = (unsigned char *) "abcdefghij245dasdfddsfdchdasdfdsdfaksldfjasdklfjasf";

  printf("Matches found: %d (Locations Requested: %d, MEM_RO == 1, MEM_RW == 0\n", findpattern(test, 28, locations, locationsRequested), locationsRequested);
  int i = 0;
  for (; i < locationsRequested; ++i) {
    printf("Location: %d, Mode: %d\n", locations[i].location, locations[i].mode);
  }

  return 0;
}
