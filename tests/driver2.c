#include "../findpattern.h"
#include <stdio.h>

void checkFindPatternAfter(unsigned char * testString, unsigned int sizeOfString) {
  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));

  printf("\nPass 2\n");
  int matchesFound = findpattern(testString, sizeOfString, locations, locationsRequested);
  printf("Total Matches: %d\n", matchesFound);

  int locationsFound = locationsRequested;
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
}

int main(int argc, char *argv[]) {
    // for formatting
  printf("test2\n");

  // memory modification description
  printf("This modification is changes the memory of the stack. In between findpattern passes four stack variable is initiated.\n\n");

  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));

  unsigned int sizeOfString = strlen(argv[1]);
  unsigned char * testString = malloc((sizeOfString+1)*sizeof(char));
  strcpy((char *) testString, argv[1]);

  printf("Pass 1\n");
  int matchesFound = findpattern(testString, sizeOfString, locations, locationsRequested);
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

  char stackVariable01[sizeOfString + 1];
  strncpy(stackVariable01, (char *) testString, sizeOfString);
  stackVariable01[sizeOfString] = '\0';

  char stackVariable02[sizeOfString + 1];
  strncpy(stackVariable02, (char *) testString, sizeOfString);
  stackVariable02[sizeOfString] = '\0';

  char stackVariable03[sizeOfString + 1];
  strncpy(stackVariable03, (char *) testString, sizeOfString);
  stackVariable03[sizeOfString] = '\0';

  char stackVariable04[sizeOfString + 1];
  strncpy(stackVariable04, (char *) testString, sizeOfString);
  stackVariable04[sizeOfString] = '\0';

  checkFindPatternAfter(testString, sizeOfString);
  return 0;
}
