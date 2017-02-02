#include "findpattern.h"
#include <stdio.h>

int main() {
  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));

  unsigned char * test = (unsigned char *) "CanYouHearMeNow";
  unsigned int sizeOfString = 15;

  printf("Matches found: %d (Locations Requested: %d, MEM_RO == 1, MEM_RW == 0\n", findpattern(test, sizeOfString, locations, locationsRequested), locationsRequested);
  int i = 0;
  for (; i < locationsRequested; ++i) {
    printf("Location: %d, Mode: %d\n", locations[i].location, locations[i].mode);
  }

  unsigned int sizeOfStringArray = 50;
  char **stringArray = malloc(sizeOfStringArray * sizeof(char *));
  int j = 0;
  for (; j < sizeOfStringArray; ++j) {
  	stringArray[j] = (char *) malloc(sizeOfString+1);
  	strcpy(stringArray[j], "CanYouHearMeNow");
  }

  printf("Matches found: %d (Locations Requested: %d, MEM_RO == 1, MEM_RW == 0\n", findpattern(test, sizeOfString, locations, locationsRequested), locationsRequested);
  int k = 0;
  for (; k < locationsRequested; ++k) {
    printf("Location: %d, Mode: %d\n", locations[k].location, locations[k].mode);
  }
  return 0;
}
