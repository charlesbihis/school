#include "Semaphore.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

sem_t *createSemaphore(int count) {
 
	// Zero _sysSem just to make sure that it doesn't have any 
	// values in it that could confuse the initialization routines
	sem_t *_sysSem = malloc(sizeof(sem_t));

	if (_sysSem) {
		memset( _sysSem, 0, sizeof( sem_t ) );
		if (sem_init(_sysSem, 0, count) != 0) {
			perror("Getting semaphore failed");
			free(_sysSem);
			_sysSem = NULL;
		}
	}
	return _sysSem;
}

void destroySemaphore(sem_t **_sysSem ) {
	if (_sysSem && *_sysSem) {
		if (sem_destroy(*_sysSem) != 0) {
			perror("Destorying semaphore failed");
		}
		else { 
			free(*_sysSem);
			*_sysSem = NULL;
		}
	}
}

void P(sem_t * _sysSem) {  // wait, lock

	if (sem_wait(_sysSem) != 0) {
		perror("Acquiring semaphore failed, blocking");
		pthread_cancel(pthread_self()); 
		for(;;) sleep(60000);
	}  
}

void V(sem_t *_sysSem) {  // signal, unlock

	if (sem_post(_sysSem) != 0) {
		perror("Releasing semaphore failed, blocking");
		pthread_cancel(pthread_self()); 
		for(;;) sleep(60000);
	}  
}


