#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/user.h>

#define MEM_RW 0
#define MEM_RO 1
#define MEM_VIO 2

// This will be used to keep track of the current mode and will help determine where to return jump to when a segmentation fault occurs.
unsigned char mode;

jmp_buf segmentViolationJumpBuffer;
jmp_buf writeViolationJumpBuffer;

struct patmatch {
	unsigned int location;
	unsigned char mode; /* MEM_RW, or MEM_RO */
};

void segmentViolationHandler(int sig);

bool isMatch(unsigned char * pattern, unsigned char * potentialPattern, unsigned int patlength);
  
unsigned int findpattern (unsigned char *pattern, unsigned int patlength,
							struct patmatch *locations, unsigned int loclength);
