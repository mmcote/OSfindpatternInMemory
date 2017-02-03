#include "findpattern.h"
#include <stdio.h>
#include <sys/mman.h>

static int alloc;

int main(void){
  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));
  unsigned char * test = (unsigned char *) "CanYouHearMeNow";
  unsigned int sizeOfString = 15;

  alloc = getpagesize();

  printf("Matches found: %d (Locations Requested: %d, MEM_RO == 1, MEM_RW == 0\n", findpattern(test, sizeOfString, locations, locationsRequested), locationsRequested);

  int i = 0;

  for (; i < locationsRequested; ++i) {
    printf("Location: %d, Mode: %d\n", locations[i].location, locations[i].mode);
  }
  
  mprotect(test, alloc, PROT_NONE);
  //make one page inaccesssible starting from the test address?

  printf("Matches found: %d (Locations Requested: %d, MEM_RO == 1, MEM_RW == 0\n", findpattern(test, sizeOfString, locations, locationsRequested), locationsRequested);

  int i = 0;

  for (; i < locationsRequested; ++i) {
    printf("Location: %d, Mode: %d\n", locations[i].location, locations[i].mode);
  }
  //call findpattern again
  
  return 0;
 }

