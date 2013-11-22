#include "Tree.h"
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

struct Tree *makeTree(const unsigned long levels)
{
	if (levels <= 0) {
		return NULL;
	}

	struct Tree *t = (Tree *) malloc (sizeof(struct Tree));
	memset(t, 0, sizeof(struct Tree));

	t->val = lrand48() % 1000;

	unsigned long i = 0;
	for (i = 0; i < MAX_BRANCH; i++) {   
		t->child[i] = makeTree(levels - 1);
	}
	return t;
}

// randomly make a tree with the total number of nodes specified, not done
Tree* randTree(unsigned long tot)
{  
	if (tot <= 0) return NULL;
	Tree *t = (Tree *)malloc(sizeof(Tree));
	t->val = lrand48() % 1000;
	
	tot --;
	int i;
	for (i = 0; i < MAX_BRANCH - 1; i++) {   
		// Choose randomly how many nodes to put in this subtree
		unsigned long nchildren = lrand48() % (tot + 1);
		t->child[i] = randTree(nchildren);
		tot -= nchildren;
	}
	// In the last subtree, use them all
	t->child[i] = randTree(tot);
	return t;
}

Tree *littleTree()
{
   
	Tree *t = NULL;

	t = (Tree *) malloc(9 * sizeof(Tree));

	t[0].val = 100;
	t[0].child[0] = t+1;  
	t[0].child[1] = t+5;
   
	t[1].val = 101;
	t[1].child[0] = t+2;
	t[1].child[1] = t+3;

	t[2].val = 102;
	t[2].child[0] = NULL;
	t[2].child[1] = NULL;

	t[3].val = 103;
	t[3].child[0] = NULL;
	t[3].child[1] = t+4;

	t[4].val = 104;
	t[4].child[0] = NULL;
	t[4].child[1] = NULL;

	t[5].val = 105;
	t[5].child[0] = t+6;
	t[5].child[1] = NULL;

	t[6].val = 106;
	t[6].child[0] = NULL;
	t[6].child[1] = t+7;

	t[7].val = 107;
	t[7].child[0] = t+8;
	t[7].child[1] = NULL;

	t[8].val = 108;
	t[8].child[0] = NULL;
	t[8].child[1] = NULL;

	return t;
}
