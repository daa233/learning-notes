INCLUDES = ../include

all: cpu mem threads io

clean:
	rm -f cpu mem threads io

cpu: cpu.c
	gcc -I $(INCLUDES) -o cpu cpu.c -Wall

mem: mem.c
	gcc -I $(INCLUDES) -o mem mem.c -Wall

threads: threads.c
	gcc -I $(INCLUDES) -o threads threads.c -Wall -pthread

io: io.c
	gcc -I $(INCLUDES) -o io io.c -Wall
