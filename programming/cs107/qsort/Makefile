CFLAGS = -Wall -g

all: main

main: main.c qsort_int.c qsort.c
	gcc -o main main.c qsort_int.c qsort.c

run:
	./main

check:
	valgrind ./main

clean:
	rm -rf main *.o