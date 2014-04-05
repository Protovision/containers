#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "array.h"
#include "dlist.h"

struct _hashtable {
	ARRAY	table;
	size_t	size;
	size_t	element_size;
	int	(*compare)(const void*, const void*);
};

typedef struct _hashtable	HASHTABLE;

size_t	_hashtable_hash(HASHTABLE *t, const void *key);
void	_hashtable_rehash(HASHTABLE *t, size_t size);

#define		hashtable_size(T)	((T)->size)

void		hashtable_init(HASHTABLE *t, size_t element_size, int (*compare)(const void*, const void*));
void		hashtable_destroy(HASHTABLE *t);
void		hashtable_clear(HASHTABLE *t);
void		hashtable_insert(HASHTABLE *t, const void *key);
int		hashtable_remove(HASHTABLE *t, const void *key);
const void	*hashtable_find(HASHTABLE *t, const void *key);



#endif
