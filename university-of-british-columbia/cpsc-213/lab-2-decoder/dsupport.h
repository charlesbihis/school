#ifndef DSUPPORT_H
#define DSUPPORT_H

#include "endian.h"

#define SHORT_INT_CODE 2
#define LONG_INT_CODE 4
#define DATA_TYPE_CODE 4
#define SINGLE_BYTE 1
#define ALL_ZEROS 0
#define ALL_ONES -1	// all zeros equals -1 in two's complement

// Purpose: to indicate the endian type of the system
// Inputs: none
// Outputs: returns - the endian type of the system and outputs a
//                  statement of the endian type of the system
//          returns - 0 if the endian type read in is invalid
int CheckSystemEndian ();

// Purpose: to indicate the endian type of the data
// Inputs: int fd - the number of bytes read in from the input
//                  file
//         char buff [] - a pointer to the file which will hold
//                        the values read
// Outputs: returns - the endian type of the data and outputs a
//                  statement of the endian type fo the data
//          returns - 0 if the endian type of the data is invalid
int CheckDataEndian (int fd, char buff[]);

// Purpose: to process the data when the endian types of both
//          the system and the data match, so no conversions
//          need to be made
// Inputs: int fd - the number of bytes read in from the input
//                  file
//         char buff [] - a pointer to the file which will hold
//                        the values read
// Outputs: will process the data and output the decoded data
//          will output an error if data is unsuccessfully decoded
void ProcessMatchingData (int fd, char buff[]);

// Purpose: to process the data when the endian types of the system
//          and the data are different, so conversions need to be
//          made
// Inputs: int fd - the number of bytes read in from the input
//                  file
//         char buff [] - a pointer to the file which will hold
//                        the values read
// Outputs: will process the data and output the decoded data
//          will output an error if data is unsuccessfully decoded
void ProcessNonmatchingData (int fd, char buff[]);

#endif
