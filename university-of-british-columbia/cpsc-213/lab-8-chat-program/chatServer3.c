// chatServer.c
// the main function of your chatServer

#include <stdio.h>
#include <signal.h> // signal
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


#include "Socket.h"
#include "Thread.h"
#include "Packet.h"
#include "Semaphore.h"


struct clientSession {
	void * socket;    // The file descriptor to the client
	// You may add additional fields to this 
	// structure if needed  
};

#define MAX_SESSIONS 3



// An array of all the currently active sessions. If a 
// slot in the array does not corespond to a currently active
// session then the socket field will be set to NULL.
struct clientSession  sessions[MAX_SESSIONS];

// A counting semaphore. This is not used until part 4 of the assignment.
sem_t  *countingSem = NULL;
sem_t  *lock = NULL;

// A chat session is the management thread entity created to manage/monitor
// a client connection. It is this functions responsibility to receive data
// from the client and then distribute it to the other clients if appropriate. 
// This routine takes a single argument, a pointer to a struct clientSession. 
// However, to be type compatible with the function address required by createThread
// the paramaterm must be of type void*

void *chatSession(void * parm) 
{
	// Add any local variable declarations here.
	// When the code in here starts executing you know that a connection was 
	// accepted from a client and that the passed in value is really a 
	// pointer to a struct clientSession. 

	// Roughly chatSession loops 
	//                reading data from the client
	//                writes the exact received data to other clients,
	//                     make sure not to send the data
	//                    back to the orginator.
	//                only send data to connected clients
	//                stop looping when EOF received
	// Make sure to close the socket, and free any allocated resources 
	// Note that the global array sessions contains all the file descriptors of
	// the open connections to clients.
	// A thread will terminate when execution runs off the end of the code  
	return NULL;
}

// Main takes a single argument, the port number to listen on.

int main (int argc, char* argv[])
{
  
	// Do not remove the following if/then/else
	// statement. This setup is needed to deal 
	// with the situation when a write is made to a 
	// socket and the other side has already closed down 

	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
		perror("sigHandle, SIGPIPE cannot be handled."); 
		exit(-1);
	}

	printf("SIGPIPE set to ignore.%d\n", SIGPIPE);


	// Add your code and variable declarations starting here.
	// Additional comments indicate some of the *important* 
	// steps the code requires. (i.e Additional actions will be
	// required for a proper implementation.) The comments should 
	// be taken as suggestions only and you may choose to implement things 
	// differently.

  



	// create the server socket to listen on




	// Loop accepting new connections and for each connection create and start
	// a thread to manage the connection. The thread uses the chatSession 
	// function. Don't forget to put in the connection information in the sessions array
	// Also, detatch the thread so that thread resources get collected.
    for (;;) {

	}
}
