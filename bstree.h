#ifndef BSTREE_H
#define BSTREE_H

#include <stdlib.h>
#include <string.h>

struct _bstree_node {
	struct _bstree_node	*left;
	struct _bstree_node	*right;
	char			key[0];
};

struct _bstree {
	struct _bstree_node	*root;
	size_t			size;
	size_t			element_size;
	int			(*compare)(const void*, const void*);
};

typedef struct _bstree BSTREE;

#define bstree_size(B)	((B)->size)

void		bstree_init(BSTREE *t, size_t element_size, int (*compare)(const void*, const void*));
void		bstree_destroy(BSTREE *t);
void		bstree_clear(BSTREE *t);
int		bstree_remove(BSTREE *t, const void *key);
const void 	*bstree_insert(BSTREE *t, const void *key);
const void	*bstree_find(BSTREE *t, const void *key);
void		bstree_iterate(BSTREE *t, void (*callback)(const void *key));

#endif

