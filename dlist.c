#include "dlist.h"

void dlist_init(DLIST *t, size_t element_size)
{
	t->first = NULL;
	t->last = NULL;
	t->size = 0;
	t->element_size = element_size;
}

void dlist_destroy(DLIST *t)
{
	dlist_clear(t);
	t->element_size = 0;
}

void _dlist_rec_clear(struct _dlist_node *node)
{
	if (node == NULL) return;
	_dlist_rec_clear(node->dn_next);
	free(node);	
}

void dlist_clear(DLIST *t)
{
	_dlist_rec_clear(t->first);
	t->first = NULL;
	t->last = NULL;
	t->size = 0;
}

struct _dlist_node *_dlist_new_node(DLIST *t, const void *data)
{
	struct _dlist_node *new;
	new = (struct _dlist_node*)malloc(sizeof(struct _dlist_node) + t->element_size);
	memcpy(new->dn_data, data, t->element_size);
	return new;
}

DLIST_ITER dlist_insert(DLIST *t, DLIST_ITER it, const void *data)
{
	struct _dlist_node *new;

	new = _dlist_new_node(t, data);
	new->dn_next = it;
	if (it == t->first) {
		new->dn_prev = NULL;
		t->first = new;
	}
	if (it == NULL) {
		new->dn_prev = t->last;
		t->last = new;	
	}
	if (new->dn_next != NULL) {
		new->dn_next->dn_prev = new;
	}
	if (new->dn_prev != NULL) {
		new->dn_prev->dn_next = new;
	}

	++t->size;
	return new;
}

DLIST_ITER dlist_remove(DLIST *t, DLIST_ITER it)
{
	struct _dlist_node *next;

	if (it == t->first) {
		t->first = it->dn_next;
	}
	
	if (it == t->last) {
		t->last = it->dn_prev;
	}

	if (it->dn_next) {
		it->dn_next->dn_prev = it->dn_prev;
	}

	if (it->dn_prev) {
		it->dn_prev->dn_next = it->dn_next;
	}

	next = it->dn_next;
	free(it);
	--t->size;
	return next;	
}

void dlist_push(DLIST *t, const void *data)
{
	dlist_insert(t, NULL, data);	
}

void dlist_unshift(DLIST *t, const void *data)
{
	dlist_insert(t, t->first, data);
}

int dlist_pop(DLIST *t, void *buffer)
{
	if (t->last == NULL) return -1;
	memcpy(buffer, t->last->dn_data, t->element_size);
	dlist_remove(t, t->last);
	return 0;
}

int dlist_shift(DLIST *t, void *buffer)
{
	if (t->first == NULL) return -1;
	memcpy(buffer, t->first->dn_data, t->element_size);
	dlist_remove(t, t->first);
	return 0;
}

int dlist_first(DLIST *t, void *buffer)
{
	if (t->first == NULL) return -1;
	memcpy(buffer, t->first->dn_data, t->element_size);
	return 0;
}

int dlist_last(DLIST *t, void *buffer)
{
	if (t->last == NULL) return -1;
	memcpy(buffer, t->last->dn_data, t->element_size);
	return 0;
}
