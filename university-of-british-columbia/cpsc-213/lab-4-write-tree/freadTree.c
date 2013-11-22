#include "Tree.h"
#include "treeMap.h"

struct Tree *freadTree(char *fname)
{
  FILE *inFile;
  inFile = fopen (fname, "r");
  int
    nodeID = 0,
    nodeValue = 0,
    leftChildID = 0,
    rightChildID = 0,
    process = 0;
 // Tree *node = (Tree*) malloc(sizeof (Tree));
  treeMap *thisMap = tm_create(4);
  int *thisNode = (int*)malloc(sizeof(int) * 4);
  
  if (inFile == 0)
  {
    printf ("ERROR: File does not exist.\n");
    return NULL;
  }  // if statement

  while (process = fread (thisNode, sizeof (int), 4, inFile))
  {
    nodeID = thisNode[0];
    nodeValue = thisNode[1];
    leftChildID = thisNode [2];
    rightChildID = thisNode [3];

    node->val = thisNode[0];
    node->child[0] = NULL;
    node->child[1] = NULL; 
    tm_insert(thisMap, nodeID, node); 
    printf ("%d %d %d %d\n", nodeID, nodeValue, leftChildID, rightChildID); 
  }  // while loop 

  rewind (inFile);

  while (process = fread (thisNode, sizeof (int), 4, inFile))
  {

  }  // while loop
  fclose (inFile);
}
