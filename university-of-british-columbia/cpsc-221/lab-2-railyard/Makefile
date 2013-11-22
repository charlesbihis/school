#Name: Charles Bihis			Class: Cpsc 221
#Student #: 43180009			Section: 203
#Login ID: i8a3				Lab Section: L2M

all: railyard stringTest

railyard: railyard.o stack_class.o queue_class.o
	g++ -o railyard railyard.o stack_class.o queue_class.o

stringTest: railyard_driver.o stack_class.o queue_class.o
	g++ -o stringTest railyard_driver.o stack_class.o queue_class.o

railyard.o: railyard.cpp stack_class.cpp stack_class.h queue_class.cpp queue_class.h
	g++ -c railyard.cpp stack_class.cpp queue_class.cpp

railyard_driver.o: railyard_driver.cpp stack_class.cpp stack_class.h queue_class.cpp queue_class.h
	g++ -c railyard_driver.cpp stack_class.cpp queue_class.cpp
