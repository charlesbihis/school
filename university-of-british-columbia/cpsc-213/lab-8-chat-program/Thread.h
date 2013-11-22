#ifndef _THREADUNIX_H
#define _THREADUNIX_H

#include <pthread.h>


struct Thread
{
	void *  (*entry_pt)(void*);
	void * arg;   // the argument passed to the thread while running
	pthread_t id; // the thread ID of this thread

};


void *createThread(void* (*func)(void*), void * parm);

// create the thread and run it
int runThread(void *vthread, pthread_attr_t *attr) ;

// Terminate this thread
int cancelThread(void * vthread);

int joinThread(void * vthread, void **thread_return);

int detachThread(void *vthread); // reaps a thread

pthread_t getThreadID(void *vthread);

void* getThreadArg(void * vthread);

#endif
