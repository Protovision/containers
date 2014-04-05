/* dlist - Doubly-Linked List */
#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>
#include <string.h>

struct _dlist_node {
	struct _dlist_node	*dn_prev, *dn_next;
	char			dn_data[0];
};

struct _dlist {
	struct _dlist_node	*first, *last;
	size_t			size;
	size_t			element_size;	
};


#define _DLIST_NEW_NODE(S)	\
	((struct _dlist_node*)malloc(sizeof(struct _dlist_node)+(S)))

typedef struct _dlist		DLIST;
typedef struct _dlist_node	*DLIST_ITER;

#define dlist_begin(T)	((T)->first)
#define dlist_end(T)	(NULL)
#define dlist_next(I)	((I)->dn_next)
#define dlist_prev(I)	((I)->dn_prev)
#define dlist_at(I)	((void*)(I)->dn_data)
#define dlist_size(T)	((T)->size)

void		dlist_init(DLIST *t, size_t element_size);
void		dlist_destroy(DLIST *t);
void		dlist_clear(DLIST *t);
DLIST_ITER	dlist_insert(DLIST *t, DLIST_ITER it, const void *data);
DLIST_ITER	dlist_remove(DLIST *t, DLIST_ITER it);
void		dlist_push(DLIST *t, const void *data);
int		dlist_pop(DLIST *t, void *buffer);
void		dlist_unshift(DLIST *t, const void *data);
int		dlist_shift(DLIST *t, void *buffer);
int		dlist_first(DLIST *t, void *buffer);
int		dlist_last(DLIST *t, void *buffer);

#endif
