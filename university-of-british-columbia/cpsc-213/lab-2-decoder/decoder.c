#include "decoder.h"

// Inputs: char *fname - a pointer to the name of the file to be decoded
// Outputs: returns true (ie non-zero) if an error has occurred during decoding
//          returns false (ie zero) if the files has been successfully decoded
int decode (char *fname)
{
  int
    system_endian = 0,  // system_endian and data_endian both initialized to 0
    data_endian = 0,    // because they will later be set to either 1 or 2
    i,
    fd;
  char
    buff [4];

  fd = open(fname, O_RDONLY);

  if (fd < 0)
  {
    perror("File open failed");
    return -2;
  }  // if statement
  
  system_endian = CheckSystemEndian ();
  data_endian =  CheckDataEndian (fd, buff);
  
  if (! system_endian)
  {
    printf ("ERROR: Invalid system endian");
    return -3;
  }  // if statement
  if (! data_endian)
  {
    printf ("ERROR: Invalid data endian");
    return -4;
  }  // if statement
  
  if (system_endian == data_endian)
  {
    printf ("\nSystem endian matches data endian.\n");
    ProcessMatchingData (fd, buff);
  }  // if statement
  else
  {
    printf ("\nSystem endian does not match data endian.\n");
    ProcessNonmatchingData (fd, buff);
  }  // else statement
  
  return 0;          // returns 0 if file has been successfully decoded
}  // decode
