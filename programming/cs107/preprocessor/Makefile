CFLAGS= -Wall -g

all: main demo

main:
	gcc -E main.c -o main.i
	gcc main.i -o main

demo:
	gcc demo.c -o demo

run:
	./main

check:
	valgrind ./main

clean:
	rm -rf main.i main demo