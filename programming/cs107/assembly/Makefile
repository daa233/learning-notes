CFLAGS= -Wall -g

all:
	cpp demo.c > demo.i
	gcc -S demo.i -o demo.s
	as demo.s -o demo.o
	gcc -o demo demo.o

run:
	./demo

check:
	valgrind ./demo

clean:
	rm -rf demo.i demo.s demo.o demo