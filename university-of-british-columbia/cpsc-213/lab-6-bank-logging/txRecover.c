#include <stdio.h>

int main (int argc, char * argv[])
{
  int bytes_read = 0;
  FILE *log_file;
  log_file = fopen (argv[1], "r");
  int *log = (int*)malloc(sizeof(int) * 1);
  int 
    typ = -1,
    pid = -1,
    trc = -1,
    tnm = -1,
    ID = -1,
    nVal = -1;
  
  //printf ("**%d", log_file);
  
  if (log_file == 0)
  {
    printf ("ERROR: File does not exist.\n");
    return NULL;
  }  // if statement
    
  while (bytes_read = fread (log, sizeof (int), 1, log_file))
  {
    typ = log [0];
    pid = log [1];
    trc = log [2];
    tnm = log [3];
    ID = log [4];
    nVal = log [-1];
    
    printf ("%d %d %d %d %d %d\n", typ, pid, trc, tnm, ID, nVal);
  }  // while loop
  
  fclose (log_file);
}  // main
