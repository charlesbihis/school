#include "endian.h"

int endian() {
  long i = 1;
  char * addr;

  addr = (char *) &i;

  return *addr? LITTLEENDIAN:BIGENDIAN;
}
