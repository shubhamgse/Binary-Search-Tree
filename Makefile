CFLAGS=-g -Wall -std=gnu11

all:program6

program6:bst.o program6.o
	gcc $(CFLAGS) bst.o program6.o -o program6

bst.o:bst.c
	gcc -c bst.c -o bst.o

program6.o:program6.c
	gcc -c program6.c -o program6.o

run:
	./program6

checkmem:program6.o bst.o
	gcc $(CFLAGS) bst.o program6.o -o program6
	valgrind --leak-check=full ./program6

clean:
	rm program6.o bst.o program6

