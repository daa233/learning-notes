CFLAGS= -Wall -g

all:
	gcc -S demo.c -o demo.s
	as demo.s -o demo.o
	gcc -o demo demo.o

run:
	./demo

check:
	valgrind ./demo

clean:
	rm -rf demo.s demo.o demo