// Tree.h
#ifndef _TREE_H
#define _TREE_H
#include <stdio.h>

#define MAX_BRANCH 2

typedef long TreeVal;

typedef struct Tree
{		
  TreeVal val; // the value of the node
  struct Tree* child[MAX_BRANCH]; // the array of its children
} Tree; 

// functions to make a Tree
Tree *randTree(unsigned long tot);
Tree *makeTree(unsigned long levels);
Tree *littleTree();

void printTree_rec (struct Tree* t, int depth, unsigned long *num); 
void printTree (Tree* t); 

// function to read a tree from a file
struct Tree *freadTree(char *fname);

// function to write a tree to a file
int fwriteTree (Tree *t, char *fname);

#endif // _TREE_H
