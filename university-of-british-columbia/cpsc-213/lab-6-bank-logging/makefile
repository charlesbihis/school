CC = gcc
CFLAGS = -g

all:	bankKey txRecover

bankKey:	bankKey.o bankApp.o bankLog.o
	$(CC) -o bankKey bankKey.o bankApp.o bankLog.o

txRecover:	txRecover.o
	$(CC) -o txRecover txRecover.o

bankKey.o:
	$(CC) -c bankKey.c

bankApp.o:
	$(CC) -c bankApp.c

bankLog.o:
	$(CC) -c bankLog.c

txRecover.o:
	$(CC) -c -g txRecover.c

clean:
	rm -f *.o *.exe bankKey *~ ./bankPro/*.cct ./bankPro/logfile
