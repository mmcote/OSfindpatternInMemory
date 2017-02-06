#include "../findpattern.h"
#include <stdio.h>
#include <sys/mman.h>


int main(int argc, char *argv[]) {
  // for formatting
  printf("test3\n");

  // memory modification description
  printf("This modification changes the memory of the heap permissions from read/write to read-only using mmap and mprotect.\n\n");

  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));

  unsigned int pageSize = getpagesize(); 
  unsigned char * copy;
  copy = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
  unsigned int sizeOfString = strlen(argv[1]);
  memcpy(copy, argv[1], sizeOfString);
  
  printf("Pass 1\n");
  int matchesFound = findpattern(copy, sizeOfString, locations, locationsRequested);
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

  mprotect(copy,pageSize,PROT_READ);
  
  printf("\nPass 2\n");
  matchesFound = findpattern(copy, sizeOfString, locations, locationsRequested);
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
