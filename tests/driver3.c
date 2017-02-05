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
  unsigned char * testString = malloc((sizeOfString+1)*sizeof(char));
  strcpy((char *) testString, "123456789123456\0");
  
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


  //change this
  //use memprotect
  /*unsigned int sizeOfStringArray = 50;
  char **stringArray = malloc(sizeOfStringArray * sizeof(char *));
  int j = 0;
  for (; j < sizeOfStringArray; ++j) {
  	stringArray[j] = (char *) malloc(sizeOfString+1);
  	strncpy(stringArray[j], (char *) testString, sizeOfString);
  }*/

  mprotect(testString, sizeOfString, PROT_READ);

  //end change
  printf("\nPass 2\n");
  matchesFound = findpattern(testString, sizeOfString, locations, locationsRequested);
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
