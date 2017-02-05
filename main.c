#include "findpattern.h"
#include <stdio.h>
#include <sys/mman.h>


int main() {
  // for formatting
  printf("test1\n");

  // memory modification description
  printf("This modification changes the memory of the address space to read-only using mprotect.\n\n");

  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));

  unsigned int sizeOfString = 15;
  
  char stackVariable01[sizeOfString + 1];
  strncpy(stackVariable01, "123456789123456\0", sizeOfString);
  stackVariable01[sizeOfString] = '\0';
  
  printf("Pass 1\n");
  int matchesFound = findpattern(stackVariable01, sizeOfString, locations, locationsRequested);
  printf("Total Matches: %d\n", matchesFound);

  int locationsFound = locationsRequested;
  if (matchesFound < locationsRequested) {
    locationsFound = matchesFound;
  }

  int i = 0;
  for (; i < locationsFound; ++i) {
    printf("0x%x\t", locations[i].location);
    if (locations[i].mode == 0) {
      printf("MEM_RW\n");
    } else {
      printf("MEM_RO\n");
    }
  }

  mprotect((void *) &stackVariable01, (size_t) sizeOfString, PROT_NONE);

  printf("\nPass 2\n");
  matchesFound = findpattern(stackVariable01, sizeOfString, locations, locationsRequested);
  printf("Total Matches: %d\n", matchesFound);

  locationsFound = locationsRequested;
  if (matchesFound < locationsRequested) {
    locationsFound = matchesFound;
  }

  int k = 0;
  for (; k < locationsFound; ++k) {
    printf("0x%x\t", locations[k].location);
    if (locations[k].mode == 0) {
      printf("MEM_RW\n");
    } else {
      printf("MEM_RO\n");
    }
  }
  return 0;
}
