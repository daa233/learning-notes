# Immediate set. Reference: https://stackoverflow.com/a/448973/6531954.
CC     := gcc
CFLAGS := -Wall -Werror -I../include 

SRCS   := thread_create.c \
	thread_create_simple_args.c \
	thread_create_with_return_args.c

# Substitution gramma: $(var:pattern=replacement)
OBJS   := ${SRCS:c=o}
PROGS  := ${SRCS:.c=}

# Explicitly tell Make the `all` here is not associated with files.
# Reference: https://stackoverflow.com/a/2145605/6531954
.PHONY: all
all: ${PROGS}

# References:
#   - https://stackoverflow.com/a/26133524/6531954
#   - https://www.gnu.org/software/make/manual/make.html#Syntax-of-Static-Pattern-Rules

# Syntax of Static Pattern Rules
# ```
# targets …: target-pattern: prereq-patterns …
# 		recipe
# 		…
# ```
# `%` can match any part of the target name; this part is called the stem.
# `%.o` matches all the *.o files.
#  It is good practice to list all included makefiles, on all prerequisite lines.
${PROGS} : % : %.o Makefile
# Automatic Variables. Reference https://www.gnu.org/software/make/manual/make.html#Automatic-Variables.
# `$<` is the automatic variable that holds the name of the prerequisite
# `$@` is the automatic variable that holds the name of the target
	${CC} $< -o $@ -pthread

clean:
	rm -f ${PROGS} ${OBJS}

%.o: %.c Makefile
	${CC} ${CFLAGS} -c $<
