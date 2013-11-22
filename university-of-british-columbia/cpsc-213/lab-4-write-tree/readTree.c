#include "Tree.h"
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int main (int argc, char* argv[])
{
	Tree *t = NULL;
  
	if (argc != 2) {
		fprintf(stderr, "Usage: readTree treeSourceFile\n");
		return -1;
	}

	char *fname = argv[1];

	struct Tree *t1 = freadTree(fname);

	if (t1 == NULL) {
		fprintf(stderr, "freadTree() returned an error\n");
		return -1;
	}

	printf("This is the tree read from %s\n", fname);
	printTree(t1);
	return 0;
}
