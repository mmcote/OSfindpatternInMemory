CC_Object = gcc -Wall -c -m32
p ?= defaultStringYouShouldChangeThis

object:
	cd tests && $(MAKE) all

tests: 
	cd tests && $(MAKE) tests

test1:
	cd tests && $(MAKE) test1

test2:
	cd tests && $(MAKE) test2

test3:
	cd tests && $(MAKE) test3

clean: 
	rm *.o -rf && cd tests && $(MAKE) clean
