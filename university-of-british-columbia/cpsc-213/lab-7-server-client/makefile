# Makefile for the Chat Service Provider Project - Assignment 7

CC=	gcc
CFLAGS=	-g -Wall

SRCO=	testServer.c testClient.c
PROG=	$(SRCO:.c=)
LIBS=	-lsocket -lnsl


all: $(PROG)

testServer: testServer.o Socket.o
	$(CC) $(CFLAGS) -o $@ testServer.o Socket.o $(LIBS)

testClient: testClient.o Socket.o
	$(CC) $(CFLAGS) -o $@ testClient.o Socket.o $(LIBS)


%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $@ 

clean:
	rm -rf $(PROG) $(OBJS) *~ *.o


testClient.o: testClient.c Socket.h
testServer.o: testServer.c Socket.h
Socket.o: Socket.c SocketStruct.h Socket.h

