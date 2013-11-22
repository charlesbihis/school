#include "Tree.h"
#include "treeMap.h"

int fwriteTree_helper (Tree *t, FILE *outFile, int nodeID);

int fwriteTree (Tree* t, char *fname)
{
  int nodeID = 1;
  FILE *outFile = NULL;
  outFile = fopen (fname,"w");

  fwriteTree_helper (t, outFile, nodeID);
  fclose (outFile);
  
  return 0;
}

int fwriteTree_helper (Tree *t, FILE *outFile, int nodeID)
{
  int
    leftTempID,
    rightTempID;

  if (t == NULL)
  {
    printf ("NULL\n");
    return;
  }  // if statement
  if (t->child[0] == NULL)
    leftTempID = 0;
  else
    leftTempID = nodeID + 1;
  if (t->child[1] == NULL)
    rightTempID = 0;
  else
    rightTempID = nodeID + 1;
  if (t->child[0] != NULL && t->child [1] != NULL)
    rightTempID = nodeID + 2;
printf ("**%d\n", t->val);
  fwrite (&nodeID, sizeof (int), 1, outFile);
  fwrite (&t->val, sizeof (long), 1, outFile);
  fwrite (&leftTempID, sizeof (int), 1, outFile);
  fwrite (&rightTempID, sizeof (int), 1, outFile);
 
  fwriteTree_helper (t->child[0], outFile, ++nodeID);
  fwriteTree_helper (t->child[1], outFile, ++nodeID);
}  // fwriteTree_helper
