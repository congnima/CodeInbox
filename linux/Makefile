CFLAGS = -g
CC = gcc

PROG = coroutine getcontext mmap setjmp ucontext sha1

all : $(PROG)

install: $(PROG)
	#install $(PROG) $(HOME)/bin/

LIBS = -lssl -lcrypto -lz

sha1 : 
	$(CC) $(CFLAGS) sha1.c -o sha1 $(LIBS)

clean:
	rm -f *.o $(PROG)
