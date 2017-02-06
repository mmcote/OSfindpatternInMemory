(name ccid id)
(Brad Hanasyk hanasyk1 1301531)
(Michael Cote mmcote 1356556)

Commands
----------------------------------------------------------------
make tests // compile and execute all tests with default pattern
make testX // compile and execute driverX with default pattern
make clean // remove all object files and test_results.txt

NOTE: To pass your own function just add p=(PATTERN) to the end of the command

Drivers
----------------------------------------------------------------
Requirement of Driver1: place instances of the pattern on the heap to see if findPattern() finds them. 
Implementation: The first driver will take in whatever pattern that is passed when compiling the driver and allocate 50 instances of the pattern on the heap.
		    Pass 1:
		    - Allcoate 1 instance of the pattern on the heap then call findpattern.
		    Pass 2:
		    - Allocate 50 more instances of the pattern on the heap then call findpattern. There should be 50 more instances of the pattern on the heap.

Requirement of Driver2: create local instances of the pattern on the stack. To do this you need to think of how you can store an instance of the pattern on the stack only after your first call to findpattern().
Implementation: The second driver will take whatever pattern that is passed when compiling the driver and allocate 4 more instances of the pattern on the stack. It can be seen that this does in fact happen by the addition of 4 more patterns found after the second pass but also by the fact that the address' follow common memory architecture with the original heap address being much lower than the four new stack addresses introduced.
		    Pass1:
		    - Allcoate 1 instance of the pattern on the heap then call findpattern.
		    Pass2:
		    - Create 4 more instances of the pattern on the stack then call findpattern. There should be 4 more instances of the pattern in total. One on the heap and four on the stack.

Requirement of Driver3: map a file into memory using mmap(2). You will then use mmap(2) to change the mode of the memory that you are mapping to. We will go over mmap(2) during the lab presentations, but feel free to look it up yourselves if you are curious.
	            Pass1:
		    - Allcoate 1 instance of the pattern on the heap then call findpattern.
		    Pass2:
		    - It can be seen after this pass that the instance on the heap has changed permissions from read/write to just read.