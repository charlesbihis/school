#include "Tree.h"
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "printTree.h"

int main (int argc, char* argv[1])
{
	srand48(time(0));

	Tree *t = NULL;
	if (argc < 2 | argc > 3) {
		fprintf(stderr, "Usage: writeTree treeDestinationFile [numberOfNodes]\n");
		return -1;
	}
	char *fname = argv[1];
	if (argc == 3) {
		t = randTree(atoi(argv[2]));
	} else {
		t = littleTree();
	}
 
	printf("This is the original tree.\n");
	printTree(t);

	int res = fwriteTree(t, fname);

	if (res < 0) {
		fprintf(stderr, "Tree writing failed\n");
		return -2;
	}
	return 0;
}
