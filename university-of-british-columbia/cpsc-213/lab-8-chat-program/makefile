# Makefile for the Chat Service Provider Project - Assignment 6

CC=	gcc
CFLAGS=	-g -Wall

SRCS=	Socket.c 
PROG= chatServer chatClient chatServer2 chatClient2 chatServer3 
LIBS=	-lnsl -lpthread -lnls -lsocket -lrt 
SUPPLIED_OBJ = Thread.o Socket.o Semaphore.o

all: $(PROG)

chatServer: chatServer.o $(SUPPLIED_OBJ)
	$(CC) $(CFLAGS) -o $@ chatServer.o $(SUPPLIED_OBJ) $(LIBS)

chatServer2: chatServer2.o $(SUPPLIED_OBJ)
	$(CC) $(CFLAGS) -o $@ chatServer2.o $(SUPPLIED_OBJ) $(LIBS)

chatServer3: chatServer3.o $(SUPPLIED_OBJ)
	$(CC) $(CFLAGS) -o $@ chatServer2.o $(SUPPLIED_OBJ) $(LIBS)

chatClient: chatClient.o $(SUPPLIED_OBJ)
	$(CC) $(CFLAGS) -o $@  chatClient.o $(SUPPLIED_OBJ) $(LIBS)
chatClient2: chatClient2.o $(SUPPLIED_OBJ)
	$(CC) $(CFLAGS) -o $@ chatClient2.o $(SUPPLIED_OBJ) $(LIBS)

chatServer.o: chatServer.c Thread.h Packet.h Semaphore.h 
chatServer2.o: chatServer2.c Thread.h Packet.h Semaphore.h 
chatServer3.o: chatServer3.c Thread.h Packet.h Semaphore.h 
chatClient.o: chatClient.c Thread.h Packet.h 
chatClient2.o: chatClient2.c Thread.h Packet.h 

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $@ 

clean:
	rm -f chatServer*.o chatClient*.o chatServer chatServer2 chatServer3 \
		chatClient2 chatClient Thread.o Semaphore.o 

