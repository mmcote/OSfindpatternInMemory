CC_Object = gcc -m32 -Wall -c
CC_Exec = gcc -m32 -Wall -o 

all: findpattern driver1 driver2
	$(CC_Exec) driver1 driver1.o findpattern.o -m32 
	$(CC_Exec) driver2 driver2.o findpattern.o -m32 

findpattern: ../findpattern.c ../findpattern.h
	$(CC_Object) ../findpattern.c

driver1: driver1.c ../findpattern.h
	$(CC_Object) driver1.c

driver2: driver2.c ../findpattern.h 
	$(CC_Object) driver2.c

run1:
	./driver1

run2:
	./driver2

clean: 
	rm *.o -rf 
