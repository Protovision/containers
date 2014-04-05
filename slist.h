/* slist - Singly-Linked List */
#ifndef SLIST_H
#define SLIST_H

#include <stdlib.h>
#include <string.h>

struct _slist_node {
	struct _slist_node	*sn_next;
	char			sn_data[0];
};

struct _slist {
	struct _slist_node	*first;
	size_t			count;
	size_t			element_size;
};

typedef struct _slist	SLIST;

#define _SLIST_NEW_NODE(S)	\
	((struct _slist_node*)malloc(sizeof(struct _slist_node)+(S)))

#define slist_size(T)	((T)->count)

void	slist_init(SLIST *t, size_t element_size);
void	slist_destroy(SLIST *t);
void	slist_clear(SLIST *t);
void	slist_unshift(SLIST *t, const void *data);
int	slist_shift(SLIST *t, void *buffer);
int	slist_first(SLIST *t, void *buffer);

typedef struct _slist_node	*SLIST_ITER;

#define	slist_begin(T)	((T)->first)
#define slist_end(T)	(NULL)
#define slist_next(I)	((I) = (I)->sn_next)
#define slist_at(I)	((void*)(I)->sn_data)


#endif

