#include "findpattern.h"
#include <stdio.h>

void checkFindPatternAfter(unsigned char * testString, unsigned int sizeOfString) {
  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));

  int matchesFound = findpattern(testString, sizeOfString, locations, locationsRequested);
  printf("Matches found: %d (Locations Requested: %d, MEM_RO == 1, MEM_RW == 0)\n", matchesFound, locationsRequested);
  
  int locationsFound = locationsRequested;
  if (matchesFound < locationsRequested) {
    locationsFound = matchesFound;
  }

  int k = 0;
  for (; k < locationsFound; ++k) {
    printf("Location: 0x%x, Mode: %d\n", locations[k].location, locations[k].mode);
  }  
}

int main() {
  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));

  unsigned int sizeOfString = 15;
  unsigned char * testString = malloc((sizeOfString+1)*sizeof(char));
  strcpy(testString, "123456789123456\0");

  int matchesFound = findpattern(testString, sizeOfString, locations, locationsRequested);
  printf("Matches found: %d (Locations Requested: %d, MEM_RO == 1, MEM_RW == 0)\n", matchesFound, locationsRequested);

  int locationsFound = locationsRequested;
  if (matchesFound < locationsRequested) {
    locationsFound = matchesFound;
  }

  int i = 0;
  for (; i < matchesFound; ++i) {
    printf("Location: 0x%x, Mode: %d\n", locations[i].location, locations[i].mode);
  }

  unsigned char stackVariable[sizeOfString + 1];
  strncpy(stackVariable, testString, sizeOfString);
  stackVariable[sizeOfString] = '\0';

  checkFindPatternAfter(testString, sizeOfString);
  return 0;
}
