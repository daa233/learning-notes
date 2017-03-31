PREFIX?=/usr/local
CFLAGS=-D_LARGEFILE64_SOURCE=1 -g -Wall -I${PREFIX}/apr/include/apr-1  -I${PREFIX}/apr/include/apr-util-1
LDFLAGS= -L${PREFIX}/apr/lib -L .aprutil-1 -L .apr-1
LDLIBS=  -lapr-1 -laprutil-1

# the following link can fix the problem that cc can't find the libraries
# http://stackoverflow.com/questions/29288248/make-is-unable-to-find-the-functions

all: devpkg

devpkg: bstrlib.o db.o shell.o commands.o

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean:
	rm -f *.o
	rm -f devpkg
	rm -rf *.dSYM