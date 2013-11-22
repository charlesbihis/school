#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "greetings.h"


// Inputs: char *fname - a pointer to the name of the file to be decoded
// Outputs: returns true (ie non-zero) if an error has occurred during decoding
//          returns false (ie zero) if the files has been successfully decoded
int decode (char *fname);

#endif
