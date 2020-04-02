CFLAGS= -Wall -g

all: main_stack_int main_stack

main_stack_int:
	gcc -o main_stack_int main_stack_int.c stack_int.c

main_stack:
	gcc -o main_stack main_stack.c stack.c

clean:
	rm -rf main_stack_int main_stack