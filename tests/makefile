CC_Object = gcc -m32 -Wall -c
CC_Exec = gcc -m32 -Wall -o 

all: findpattern test1 test2

findpattern: ../findpattern.c ../findpattern.h
	$(CC_Object) ../findpattern.c

driver1: test1.c ../findpattern.h
	$(CC_Object) test1.c
	$(CC_Exec) test1 test1.o findpattern.o -m32

driver2: test2.c ../findpattern.h 
	$(CC_Object) test2.c
	$(CC_Exec) test2 test2.o findpattern.o -m32

test1: driver1
	./test1 >> results_test.txt
	echo "" >> results_test.txt

test2: driver2
	./test2 >> results_test.txt
	echo "" >> results_test.txt

clean: 
	rm *.o -rf && rm -rf test_results.txt
