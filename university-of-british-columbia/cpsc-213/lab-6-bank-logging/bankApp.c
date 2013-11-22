//////////////////////////////////////////////////////////////////////
// Name: Charles Bihis							Course: Cpsc 213	//
// Student #: 43180009							Class Section: 203	//
// Date: March 15, 2005							Lab Section L2M		//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>
#include "bankApp.h"

#define MAX_PATH 50
#define MAX_LENGTH 255

int openOrCreateAcct (int *const acctFd, const unsigned long acctNum)
{
  char path[MAX_PATH];

  sprintf(path, "./%s%lu%s", DIR_BANK, acctNum, SUF_BANK);
  *acctFd = open(path, O_RDWR | O_CREAT, 0600);
  
  if (*acctFd < 0)
  {
    *acctFd = -1;
	return -1;
  }  // if statement
  
  return 0;
}  // openOrCreateAcct


int getBalance (const int acctFd, long *balance)
{
  int bytes_read = 0;
  char *buffer = (char*)malloc(MAX_LENGTH);
  
  lseek (acctFd, 0L, 0);
  bytes_read = read (acctFd, buffer, MAX_LENGTH);
  *balance = atoi (buffer);
  free (buffer);
  
  if (bytes_read == 0)
  { 
    setBalance (acctFd, 0);
    return -1;
  }  // if statement
  
  return 0;
}  // getBalance


int setBalance (const int acctFd, const long balance)
{
  int bytes_read = 0;
  int output_length;
  char *output = (char*) malloc(255);

  lseek (acctFd, 0L, 0);
  ftruncate (acctFd, 0);
  sprintf(output, "%lu", balance);
  for (output_length = 0; output[output_length]; output_length++);
  bytes_read = write (acctFd, output, output_length);
	
  if (bytes_read <= 0)
    return -1;

  return 0;
}  // setBalance
