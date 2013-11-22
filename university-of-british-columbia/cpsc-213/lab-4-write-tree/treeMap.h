#ifndef TREE_MAP_H
#define TREE_MAP_H
#include "Tree.h"

typedef struct treeMapEntry {
	unsigned int id;
	Tree *t;
} treeMapEntry;

typedef struct treeMap {
	unsigned int capacity, size;
	treeMapEntry *map;
} treeMap;

// Create a new tree map with the given initial size.
// Treemaps grow as necessary so giving a good initial size is merely a
// performance optimization.
treeMap *tm_create(int size);

// Return the tree with the given id, or 0 if the id is not found
Tree *tm_treeof(treeMap *tm, unsigned int id);

// Return the id of the tree, or 0 if not found
unsigned int tm_idof(treeMap *tm, Tree *t);

// Insert a new id/tree pair into the map.  Duplicates are not detected.
void tm_insert(treeMap *tm, unsigned int id, Tree *t);

// Free all the storage associated with the treemap
void tm_destroy(treeMap *tm);
#endif
