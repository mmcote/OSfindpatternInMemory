CC_Object = gcc -m32 -Wall -c
CC_Exec = gcc -m32 -Wall -o 

all: findpattern driver1 driver2 driver3

tests: findpattern test1 test2 test3

findpattern: ../findpattern.c ../findpattern.h
	$(CC_Object) ../findpattern.c

driver1: driver1.c ../findpattern.h
	$(CC_Object) driver1.c
	$(CC_Exec) test1 driver1.o findpattern.o

driver2: driver2.c ../findpattern.h 
	$(CC_Object) driver2.c
	$(CC_Exec) test2 driver2.o findpattern.o

driver3: driver3.c ../findpattern.h 
	$(CC_Object) driver3.c
	$(CC_Exec) test3 driver3.o findpattern.o

test1: findpattern driver1
	./test1 $(p) >> test_results.txt
	echo "" >> test_results.txt

test2: findpattern driver2
	./test2 $(p) >> test_results.txt
	echo "" >> test_results.txt

test3: findpattern driver3
	./test3 $(p) >> test_results.txt
	echo "" >> test_results.txt

clean: 
	rm *.o -rf && rm -rf test_results.txt
