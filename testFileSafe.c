#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <stdbool.h>

#define MEM_RW 0
#define MEM_RO 1
#define MEM_VIO 2

// This will be used to keep track of the current mode and will help determine where to return jump to when a segmentation fault occurs.
unsigned char mode;

jmp_buf segmentViolationJumpBuffer;
jmp_buf writeViolationJumpBuffer;

struct patmatch {
  unsigned int location;
  unsigned char mode;
};

// --Valid
void segmentViolationHandler(int sig) {
  // occured when attempting to read the page
  if (mode == MEM_VIO) {
    longjmp(segmentViolationJumpBuffer, 1);
  // occured when trying to write to the page
  } else if (mode == MEM_RO) {
    longjmp(writeViolationJumpBuffer, 1);
  }
}

bool isMatch(unsigned char * pattern, unsigned char * potentialPattern, unsigned int patlength) {
  int i = 0;
  for(; i < patlength; ++i) {
    if (pattern[i] != potentialPattern[i]) {
      return false;
    }
  }
  return true;
}

unsigned int findpattern (unsigned char * pattern, unsigned int patlength, struct patmatch *locations, unsigned int loclength) {
  // create sigaction for handling SIGSEGV
  struct sigaction segmentViolationAction;
  segmentViolationAction.sa_handler = segmentViolationHandler;
  sigemptyset(&segmentViolationAction.sa_mask);
  segmentViolationAction.sa_flags = 0;
  sigaction(SIGSEGV, &segmentViolationAction, 0);

  // Number of matches found
  int count= 0;

  unsigned char * currentAddress = (unsigned char*) 0x00000000;
  unsigned int maxAddress = 0xffffffff;

  unsigned int page = 0;
  unsigned int pageSize = getpagesize();
  int numPages = maxAddress/pageSize;
  while(true) {
    mode = MEM_VIO;
    
    // Skip page if not able to read page / segfault
    if (sigsetjmp(segmentViolationJumpBuffer,1)) {
      currentAddress += pageSize;
    }
    if (page >= numPages) {
      return count;
    }
    ++page;

    // check if we are able to read the page, expect segmentation fault
    char testRead = (char) *currentAddress;
    mode = MEM_RO;

    int byteNum = 0;    
    unsigned char * addressTesting = currentAddress;
    while (byteNum < pageSize) {

      // set mode back to mem_violation as there may be a violation for an individual byte
      mode = MEM_VIO;

      //      if(memcmp(pattern, addressTesting, patlength) == 0) {
      if(isMatch(pattern, addressTesting, patlength)) {
	printf("Pattern to compare: %s\n", pattern);
	//	printf("Bytes to compare: %s\n", bytesToCmp);
	printf("Match found.\n");
	printf("Address found: %p\n", addressTesting);
	
	// set mode to mem_ro as we know we can read the entire space with the matching pattern
	mode = MEM_RO;
	if (count <= loclength) {
	  // we know we can read test once to see if we can write to page
	  if (sigsetjmp(writeViolationJumpBuffer, 1) == 0) {
	    *addressTesting = 'a';
	    mode = MEM_RW;
	    longjmp(writeViolationJumpBuffer, 1);
	  } else if(mode == MEM_RW) {
	    printf("SUCCESS\n");
	  } else {
	    printf("FAIL\n");
	  }
          locations[count].location = page*pageSize + byteNum;
          locations[count].mode = mode;
	}
	addressTesting += patlength;
	++count;
      } else {
	++addressTesting;
      }
      ++byteNum;
    }
    // Go to the next page if we were able to successfully search the whole page
    currentAddress += pageSize;
  }
  return count;
}

int main() {
  int locationsRequested = 20;
  struct patmatch * locations = malloc(locationsRequested*sizeof(struct patmatch));
  unsigned char * test = (unsigned char *) "CarlIsMagi";

  printf("Matches found: %d", findpattern(test, 10, locations, locationsRequested));
  int i = 0;
  for (; i < locationsRequested; ++i) {
    printf("Location: %d, Mode: %c", locations[i].location, locations[i].mode);
  }

  return 0;
}