CC = gcc
CFLAGS = -g

all:	readTree writeTree fileIO

readTree:	readTree.o freadTree.o printTree.o treeMap.o
	$(CC) -o readTree readTree.o freadTree.o printTree.o treeMap.o


writeTree:	writeTree.o fwriteTree.o printTree.o Tree.o treeMap.o
	$(CC) -o writeTree writeTree.o fwriteTree.o printTree.o Tree.o treeMap.o

fileIO:		fileIO.o
	$(CC) -o fileIO fileIO.o

clean:
	rm -f *.o *.exe readTree writeTree fileIO *~ 
