
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>


#include "printTree.h"

void printTree_rec (struct Tree* t, int depth, unsigned long *num)
{
	int l;
	for (l = 0; l < depth; l++) printf("  ");
	printf("t%lu adr=0x%lx val=%ld\n", *num, t, t->val);

	++*num;
	unsigned long i = 0;
	for (i = 0; i < MAX_BRANCH; i++) {
		if (t->child[i]) {
			printTree_rec(t->child[i], depth + 1, num);
		} else {
			for (l = 0; l < (depth + 1); l++) printf("  ");
			printf("NULL\n");
		}
	}
}


void printTree(struct Tree* t)
{
	unsigned long num = 0;
	printTree_rec(t, 0, &num);

	printf("Number of nodes of Tree t (0x%lx) = %lu \n", t, num);
}
