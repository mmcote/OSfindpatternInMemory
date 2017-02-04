#include "findpattern.h"

void segmentViolationHandler(int sig) {
  // occured when attempting to read the page
  if (mode == MEM_VIO) {
    siglongjmp(segmentViolationJumpBuffer, 1);
    // occured when trying to write to the page
  } else if (mode == MEM_RO) {
    siglongjmp(writeViolationJumpBuffer, 1);
  }
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

      bool match = true;
      int i = 0;
      for(; i < patlength; ++i) {
        if (pattern[i] != addressTesting[i]) {
          match = false;
        }
      }

      if(match) {
        // set mode to mem_ro as we know we can read the entire space with the matching pattern
        mode = MEM_RO;
        if (count <= loclength) {
          // we know we can read test once to see if we can write to page
          if (sigsetjmp(writeViolationJumpBuffer, 1) == 0) {
            char tempVar = *addressTesting;
            *addressTesting = tempVar;
            mode = MEM_RW;
            siglongjmp(writeViolationJumpBuffer, 1);
        }
          locations[count].location = (unsigned int) addressTesting;
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
