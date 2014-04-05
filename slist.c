#include "slist.h"

void	slist_init(SLIST *t, size_t element_size)
{
	t->element_size = element_size;
	t->count = 0;
	t->first = NULL;
}

void	slist_destroy(SLIST *t)
{
	slist_clear(t);
	t->element_size = 0;
	t->count = 0;
	t->first = NULL;
}

void	slist_clear(SLIST *t)
{
	struct _slist_node *node, *next;
	for (node = t->first; node != NULL; node = next) {
		next = node->sn_next;
		free(node);
	}
}

void	slist_unshift(SLIST *t, const void *data)
{
	struct _slist_node *node;
	node = _SLIST_NEW_NODE(t->element_size);
	if (node == NULL) return;
	memcpy(node->sn_data, data, t->element_size);
	node->sn_next = t->first;
	t->first = node;
	++t->count;	
}

int	slist_first(SLIST *t, void *buffer)
{
	if (t->first == NULL) return -1;
	memcpy(buffer, t->first->sn_data, t->element_size);
	return 0;
}

int	slist_shift(SLIST *t, void *buffer)
{
	struct _slist_node *node;
	if (slist_first(t, buffer) < 0) return -1;
	node = t->first;
	t->first = t->first->sn_next;
	free(node);
	--t->count;
	return 0;
}

