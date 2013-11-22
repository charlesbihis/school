#ifndef _SEMAPHOREUNIX_H
#define _SEMAPHOREUNIX_H

#include <semaphore.h>

void destroySemaphore(sem_t **_sysSem);
sem_t *createSemaphore(int count);
void P(sem_t *);
void V(sem_t *);

#endif
