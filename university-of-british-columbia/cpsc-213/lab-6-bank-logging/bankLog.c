//////////////////////////////////////////////////////////////////////
// Name: Charles Bihis							Course: Cpsc 213	//
// Student #: 43180009							Class Section: 203	//
// Date: March 15, 2005							Lab Section L2M		//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bankLog.h"

int recordlog (int flog, const struct txRec *const recP)
{
  int bytes_written = 0;
  char *buffer = (char*)malloc(255);

  lseek (flog, 0, SEEK_SET);
  lockf(flog, F_LOCK, 1);

  lseek (flog, 0, SEEK_END);

  sprintf(buffer, "-----BEGIN-----\n%u\n", recP->typ );
  bytes_written = write(flog, buffer, strlen(buffer));
  if (bytes_written < 0)
  {
	printf("ERROR: log recording unsuccessful\n");
	return -1;
  }  // if statement
  
  sprintf(buffer, "%d\n", recP->pid );
  bytes_written = write(flog, buffer, strlen(buffer));
  if (bytes_written < 0)
  {
	printf("ERROR: log recording unsuccessful\n");
	return -1;
  }  // if statement
	
  sprintf(buffer, "%lu\n", recP->trc );
  bytes_written = write(flog, buffer, strlen(buffer));
  if (bytes_written < 0)
  {
	printf("ERROR: log recording unsuccessful\n");
	return -1;
  }  // if statement
	
  sprintf(buffer, "%lu\n", recP->tnm );
  bytes_written = write(flog, buffer, strlen(buffer));
  if (bytes_written < 0)
  {
	printf("ERROR: log recording unsuccessful\n");
	return -1;
  }  // if statement
	
  sprintf(buffer, "%lu\n", recP->ID );
  bytes_written = write(flog, buffer, strlen(buffer));
  if (bytes_written < 0)
  {
	printf("ERROR: log recording unsuccessful\n");
	return -1;
  }  // if statement
	
  sprintf(buffer, "%lu\n-----END-----\n\n", recP->nVal );
  bytes_written = write(flog, buffer, strlen(buffer));
  if (bytes_written < 0)
  {
	printf("ERROR: log recording unsuccessful\n");
	return -1;
  }  // if statement
	
  lseek (flog, 0, SEEK_SET);
  lockf(flog, F_ULOCK, 1);

  return 0;
}
