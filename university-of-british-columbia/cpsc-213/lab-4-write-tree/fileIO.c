#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

#define BLK_SIZE 8192
#define MAX_FILE_SIZE (25 * 1024 * 1024)
#define TMP_FILE_PREFIX "213IO" // temporary file name prefix

typedef int bool; // C does not have boolean values
#define false 0
#define true 1


#undef min
static inline long min(long a, long b)
{
  return a < b ? a : b;
}

typedef enum { kRead, kFRead, kWrite, kFWrite } Operation;

const char *text(Operation o)
{
  return
    o == kRead ? "read" :
    o == kFRead ? "fread" :
    o == kWrite ? "write" :
    o == kFWrite ? "fwrite" :
    "undefined operation";
}
    
bool doingReads(Operation o)
{
  return o == kRead || o == kFRead;
}

bool doingBufferedIO(Operation o)
{
  return o == kFRead || o == kFWrite;
}

bool doingWrites(Operation o)
{
  return o == kWrite || o == kFWrite;
}

///
// Build a random block

char* composeText(char* text, unsigned long size)
{
  unsigned long i = 0;

  srand48(time(0)); // plant seed
  for (i = 0; i < size; i++) {
    text[i] = 0x20 + lrand48() % 0x60;
  }

  return text;
}

void shuffleAry(unsigned long* ary, const unsigned long size)
{
  srand48(time(0)); // plant seed

  unsigned long i = 0;  

  // First fill them in
  for (i = 0; i < size; i++)
    ary[i] = i;

  // And then swap some.  Swapping 4 times as many elements are in the
  // array ought to shuffle them pretty good.
  for (i = 0; i < 4 * size; i++)
  {
    unsigned long pos1 = lrand48() % size, pos2 = lrand48() % size;
    unsigned long t = ary[pos1];
    ary[pos1] = ary[pos2];
    ary[pos2] = t;
  }
}

int main (int argc, char* args[])
{
    /*
     f = the size of the file
     n = number of blocks = f / BLK_SIZE + (bool)f%BLK_SIZE

     fname = the name of the file
    */

  unsigned long b = BLK_SIZE, f = MAX_FILE_SIZE; // std filesize is 100MB
  int ret;
  char *fname = tempnam("/tmp", cuserid(NULL));
  char *blk;
  bool random = false;
  Operation operation = kFWrite;

  unsigned long i = 0;

  for (i = 1; i < argc; i++)
  {
    if ((args[i][0] == 'b') && (args[i][1] == '=') && (strlen(args[i]) > 2))
    {
      b = atol(&args[i][2]);
      if (b < 0 || b > MAX_FILE_SIZE)
      {
        fprintf(stderr, "Illegal block size %d\n", b);
        fflush(stderr);
        b = BLK_SIZE;
      }
    }

    else if ((args[i][0] == 'f') && (args[i][1] == '=') && (strlen(args[i]) > 2))
    {
      f = atol(&args[i][2]);
      if (f < 0 || f > MAX_FILE_SIZE)
      {
        fprintf(stderr, "Illegal block size %d\n", f);
        fflush(stderr);
        f = MAX_FILE_SIZE;
      }
    }

    else if (strcmp(args[i], "random") == 0)
    {
      random = true;
    }

    else if (strcmp(args[i], "read") == 0)
    {
      operation = kRead;
    }

    else if (strcmp(args[i], "fread") == 0)
    {
      operation = kFRead;
    }

    else if (strcmp(args[i], "write") == 0)
    {
      operation = kWrite;
    }

    else if (strcmp(args[i], "fwrite") == 0)
    {
      operation = kFWrite;
    }

    else
    {
      free(fname);
      fname = args[i];
    }
  }


  // create the data block and initialize it if necessary
  blk = (char *) calloc(b, sizeof(char));
  if (doingWrites(operation))
    composeText(blk, b);

  // Open the data files
  FILE *file;
  int filedes;
  bool error = 0;

  switch (operation)
  {
    case kRead:
      filedes = open(fname, O_RDONLY);
      error = filedes < 0;
      break;

    case kWrite:
      filedes = open(fname, O_CREAT|O_EXCL|O_WRONLY, S_IRWXU);
      error = filedes < 0;
      if (error) break; 
      unlink(fname);
      break;

    case kFRead:
      file = fopen(fname, "r");
      error = file == NULL;
      break;
  
    case kFWrite:
      filedes = open(fname, O_CREAT|O_EXCL|O_WRONLY, S_IRWXU);
      error = filedes < 0;
      if (error) break ;
      unlink(fname);
      file = fdopen(filedes, "w");
      error = file == NULL;
      break;
  }
  
  if (error)
  {
    perror("fileIO: Can't open file");
    return errno;
  }

  if (doingReads(operation))
  {
    struct stat buf;    // make stat(2) call
    stat(fname, &buf);    // check filesize
    f = buf.st_size;
  }

  unsigned long n = f/b + ((f%b)?1:0);
  // n has the number of times to perform the I/O operation, the last 
  // operation may not be a full block
  unsigned long last_write_size = f % b;
  unsigned long *randomBlockOrder = NULL;

  if (random)
  {
    randomBlockOrder = (unsigned long *) calloc(n, sizeof(long));
    shuffleAry(randomBlockOrder, n);
  }

  // testing
  printf("f: %lu \tb: %lu \tn: %lu\n", f, b, n);
  printf("%s\t%s\t%s\n", random ? "random" : "", text(operation), fname);

  // Flush the IO buffers before starting the I/O
  fflush(stdout);
  fflush(stderr);

  // start timing
  struct timeval t1, t2;
  gettimeofday(&t1, 0);

  unsigned long pos = 0;
  unsigned  bytes_left = f; 
  //  for (i = 0, pos = 0; pos < f; i++, pos += b)
  while (bytes_left) {
    int io_size;
    io_size =  (bytes_left >b)?b:bytes_left;
    if (random)
    {
      if (doingBufferedIO(operation))
        ret = fseek(file, pos = randomBlockOrder[i] * b, SEEK_SET);
      else
        ret = lseek(filedes, pos = randomBlockOrder[i] * b, SEEK_SET);
      if (ret < 0)
      {
        fprintf(stderr, "Positioning error on operation %ld at position %ld\n", i, pos);
        perror("Error:");
      }
    }

    switch(operation)
    {
      case kRead:
        ret = read(filedes, blk, io_size);
        break;

      case kWrite:
        ret = write(filedes, blk, io_size);
        break;

      case kFRead:
        ret = fread(blk, sizeof(char), io_size, file);
        break;

      case kFWrite:
        ret = fwrite(blk, sizeof(char), io_size, file);
        break;
    }

    if (ret < 0)
    {
      perror("Error on IO operation:");
      break;
    }
    
    bytes_left -= ret;
  }


  gettimeofday(&t2, 0); // end timing

  printf("Time : %ld (secs) + %ld (usecs) \n",
       (t2.tv_sec - t1.tv_sec - ((bool) (t1.tv_usec > t2.tv_usec))),
       (t2.tv_usec - t1.tv_usec + ((bool) (t1.tv_usec > t2.tv_usec))*1000000));

  return 0;
}

