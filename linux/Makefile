CFLAGS = -g
CC = gcc

PROG = sha1 service

all : $(PROG)

install: $(PROG)
	#install $(PROG) $(HOME)/bin/

LIBS = -lssl -lcrypto -lz

sha1: 
	$(CC) $(CFLAGS) sha1.c -o sha1 $(LIBS)

service:
	$(CC) $(CFLAGS) service.cpp -o service $(LIBS)

clean:
	rm -f *.o $(PROG)
