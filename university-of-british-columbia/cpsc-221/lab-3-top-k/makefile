# Name: Charles Bihis		Course: Cpsc 221
# Student #: 43180009		Class Section: 201
# Date: April 2, 2005		Lab Section: L2M

all: topk

topk: MapBST.o Pair.o topk.o
	g++ -o topk MapBST.o Pair.o topk.o

topk.o: topk.cpp
	g++ -c topk.cpp

MapBST.o: MapBST.cpp
	g++ -c MapBST.cpp

Pair.o: Pair.cpp
	g++ -c Pair.cpp

clean:
	rm -rf *.o topk

