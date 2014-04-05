#include "hashtable.h"

void hashtable_init(HASHTABLE *t, size_t element_size, int (*compare)(const void*, const void*))
{
	size_t i;
	array_init(&t->table, sizeof(DLIST));
	array_resize(&t->table, 10);
	for (i = 0; i != 10; ++i) {
		dlist_init((DLIST*)array_at(&t->table, i), element_size);
	}	
	t->size = 0;
	t->element_size = element_size;
	t->compare = compare;
}

void hashtable_destroy(HASHTABLE *t)
{
	size_t i, j;
	j = array_size(&t->table);
	for (i = 0; i != j; ++i) {
		dlist_destroy((DLIST*)array_at(&t->table, i));
	}
	array_destroy(&t->table);
}

size_t _hashtable_hash(HASHTABLE *t, const void *key)
{
	size_t hash, len;
	const char *cptr;

	hash = 2166136261UL;
	len = t->element_size;
	cptr = (const char*)key;

	for (; len; --len) {
		hash = (hash*131) + *cptr++;
	}
	
	return hash;	
}

void _hashtable_rehash(HASHTABLE *t, size_t newsize)
{
	ARRAY table;
	DLIST *bucket;
	size_t i, j, hash;
	DLIST_ITER it, end;

	array_init(&table, sizeof(DLIST));
	array_resize(&table, newsize);
	for (i = 0; i != newsize; ++i) {
		dlist_init((DLIST*)array_at(&table, i), t->element_size);
	}
	
	j = array_size(&t->table);
	for (i = 0; i != j; ++i) {
		bucket = (DLIST*)array_at(&t->table, i);
		if (dlist_size(bucket)) {
			end = dlist_end(bucket);
			for (it = dlist_begin(bucket); it != end; it = dlist_next(it)) {
				hash = _hashtable_hash(t, dlist_at(it)) % newsize;
				dlist_push((DLIST*)array_at(&table, hash), dlist_at(it));
			}	
		}
	}
	array_destroy(&t->table);
	memcpy(&t->table, &table, sizeof(ARRAY));
}

void hashtable_insert(HASHTABLE *t, const void *key)
{
	size_t size, hash;
	DLIST *bucket;
	DLIST_ITER it, end;

	size = array_size(&t->table);
	if ((long double)t->size / size >= 0.77) {
		_hashtable_rehash(t, size*2);
	}
	size = array_size(&t->table);
	hash = _hashtable_hash(t, key) % size;
	
	bucket = (DLIST*)array_at(&t->table, hash);
	end = dlist_end(bucket);
	for (it = dlist_begin(bucket); it != end; it = dlist_next(it)) {
		if (t->compare(key, dlist_at(it)) == 0) {
			memcpy(dlist_at(it), key, t->element_size);
			return;
		}
	}
	dlist_push(bucket, key);
	++t->size;
}

int hashtable_remove(HASHTABLE *t, const void *key)
{
	size_t hash;
	DLIST *bucket;
	DLIST_ITER it, end;
	
	hash = _hashtable_hash(t, key) % array_size(&t->table);
	bucket = (DLIST*)array_at(&t->table, hash);
	if (dlist_size(bucket) == 0) return -1;
	end = dlist_end(bucket);
	for (it = dlist_begin(bucket); it != end; it = dlist_next(it)) {
		if (t->compare(key, dlist_at(it)) == 0) {
			dlist_remove(bucket, it);
			--t->size;
			return 0;
		}
	}
	return -1;
}

const void *hashtable_find(HASHTABLE *t, const void *key)
{
	size_t hash;
	DLIST *bucket;
	DLIST_ITER it, end;

	hash = _hashtable_hash(t, key) % array_size(&t->table);
	bucket = (DLIST*)array_at(&t->table, hash);
	if (dlist_size(bucket) == 0) return NULL;
	end = dlist_end(bucket);
	for (it = dlist_begin(bucket); it != end; it = dlist_next(it)) {
		if (t->compare(key, dlist_at(it)) == 0) {
			return dlist_at(it);
		}
	}
	return NULL;
}

void hashtable_clear(HASHTABLE *t)
{
	size_t i, j;
	j = array_size(&t->table);
	for (i = 0; i != j; ++i) {
		dlist_clear((DLIST*)array_at(&t->table, i));
	}
	t->size = 0;
}
