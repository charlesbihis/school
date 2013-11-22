#include "dsupport.h"

// Purpose: to indicate the endian type of the system
// Inputs: none
// Outputs: returns - the endian type of the system and outputs a
//                  statement of the endian type of the system
//          returns - 0 if the endian type read in is invalid
int CheckSystemEndian ()
{
  int endianness;
  
  endianness = endian();

  if (endianness == BIGENDIAN)
  {
    printf("\nThe endian of the system is big endian");
    return BIGENDIAN;
  }  // if statement
  else if (endianness == LITTLEENDIAN)
  {
    printf ("\nThe endian of the system is little endian");
    return LITTLEENDIAN;
  }  // else if statement
  else
    return 0;
}  // CheckSystemEndian

// Purpose: to indicate the endian type of the data
// Inputs: int fd - the number of bytes read in from the input
//                  file
//         char buff [] - a pointer to the file which will hold
//                        the values read
// Outputs: returns - the endian type of the data and outputs a
//                  statement of the endian type fo the data
//          returns - 0 if the endian type of the data is invalid
int CheckDataEndian (int fd, char buff[])
{
  int i, endianness;

  i = read(fd, buff, DATA_TYPE_CODE);
  endianness = * buff;

  if (endianness == ALL_ONES)
  {
    printf ("\nThe endian of the data is big endian\n");
    return BIGENDIAN;
  }  // if statement
  else if (endianness == ALL_ZEROS)
  {
    printf ("\nThe endian of the data is little endian\n");
    return LITTLEENDIAN;
  }  // else if statement
  else
    return 0;
}  // CheckDataEndian

// Purpose: to process the data when the endian types of both
//          the system and the data match, so no conversions
//          need to be made
// Inputs: int fd - the number of bytes read in from the input
//                  file
//         char buff [] - a pointer to the file which will hold
//                        the values read
// Outputs: will process the data and output the decoded data
//          will output an error if data is unsuccessfully decoded
void ProcessNonmatchingData (int fd, char buff[])
{
  int
    i,
    j,
    data_type,
    data_value,
    string_length;
  
  while (i = read (fd, buff, DATA_TYPE_CODE))
  {
    data_type = buff [0];
    if (data_type == SHORT_INT_CODE)
    {
      read (fd, buff, SHORT_INT_CODE);
      data_value = *buff;
      printf ("\n* short int: %d", data_value);
    }  // if statement
    else if (data_type == LONG_INT_CODE)
    {
      read (fd, buff, LONG_INT_CODE);
      data_value = *buff;
      printf ("\n* long int: %d", data_value);
    }  // else if statement
    else if (data_type < 0)
    {
      printf ("\n* string: \"");
      string_length = (data_type * -1);
      
      for (j = 0; j < string_length; j++)
      {
        read (fd, buff, SINGLE_BYTE);
        data_type = buff [0];
        printf ("%c", data_type);
      }  // for loop
      
      printf ("\" (%d)", string_length);
    }  // else if statement
    else
      printf ("\nERROR: invalid data type %d", data_type);
  }  // while loop
}  // ProcessMatchingData

// Purpose: to process the data when the endian types of the system
//          and the data are different, so conversions need to be
//          made
// Inputs: int fd - the number of bytes read in from the input
//                  file
//         char buff [] - a pointer to the file which will hold
//                        the values read
// Outputs: will process the data and output the decoded data
//          will output an error if data is unsuccessfully decoded
void ProcessMatchingData (int fd, char buff[])
{
  int
    i=0,
    j,
    data_type,
    data_value,
    string_length;

  while (i = read (fd, buff, DATA_TYPE_CODE))
  {
    data_type = buff[3];
    if (data_type == SHORT_INT_CODE)
    {
      read (fd, buff, SHORT_INT_CODE);
      data_value = *buff;
      printf ("\n* short int: %d", data_value);
    }  // if statement
    else if (data_type == LONG_INT_CODE)
    {
      read (fd, buff, LONG_INT_CODE);
      data_value = *buff;
      printf ("\n* long int: %d", data_value);
    }  // else if statement
    else if (data_type < 0)
    {
      printf ("\n* string: \"");
      string_length = (data_type * -1);
      
      for (j = 0; j < string_length; j++)
      {
        read (fd, buff, SINGLE_BYTE);
        data_type = buff [0];
        printf ("%c", data_type);
      }  // for loop
      
      printf ("\" (%d)", string_length);
    }  // else if statement
    else
      printf ("\nERROR: invalid data type %d", data_type);
  }  // while loop
}  // ProcessNonmatchingData
