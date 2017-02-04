CC_Object = gcc -Wall -c -m32

object:
	$(CC_Object) findpattern.c 
test: 
	$(MAKE) -C tests
clean: 
	rm *.o -rf 
