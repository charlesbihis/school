#include "treeMap.h"

treeMap *tm_create(int size)
{
	treeMap *tm = (treeMap *)malloc(sizeof(treeMap));
	tm->capacity = size;
	tm->size = 0;
	tm->map = (treeMapEntry *)malloc(tm->capacity * sizeof(treeMapEntry));
	return tm;
}

Tree *tm_treeof(treeMap *tm, unsigned int id)
{
	int i;
	for (i = 0; i < tm->size; ++i) {
		if (tm->map[i].id == id)
			return tm->map[i].t;
	}
	return NULL;
}

unsigned int tm_idof(treeMap *tm, Tree *t)
{
	int i;
	for (i = 0; i < tm->size; ++i) {
		if (tm->map[i].t == t)
			return tm->map[i].id;
	}
	return 0;
}

void tm_insert(treeMap *tm, unsigned int id, Tree *t)
{
	if (tm->size >= tm->capacity) {
		tm->capacity *= 2;
		tm->map = (treeMapEntry *)realloc(tm->map);
	}
	tm->map[tm->size].id = id;
	tm->map[tm->size].t = t;
	tm->size ++;
}

void tm_destroy(treeMap *tm)
{
	free(tm->map);
	free(tm);
}
