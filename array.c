#include "array.h"

void array_init(ARRAY *a, size_t element_size)
{
	a->a_base = NULL;
	a->a_dend = NULL;
	a->a_end = NULL;
	a->element_size = element_size;
}

void array_destroy(ARRAY *a)
{
	if (a->a_base) {
		free(a->a_base);
		a->a_base = NULL;
	}
}

void array_push(ARRAY *a, const void *data)
{
	ptrdiff_t dend_diff, end_diff;

	if (a->a_dend == a->a_end) {
		dend_diff = a->a_dend-a->a_base;
		end_diff = a->a_end-a->a_base;
		if (end_diff == 0) end_diff = a->element_size * 2;
		else end_diff *= 2;
		a->a_base = (char*)realloc(a->a_base, end_diff);
		a->a_dend = a->a_base + dend_diff;
		a->a_end = a->a_base + end_diff;	
	}

	memcpy(a->a_dend, data, a->element_size);
	a->a_dend += a->element_size;	
}

int array_pop(ARRAY *a, void *buffer)
{
	if (a->a_dend == a->a_base) return -1;
	a->a_dend -= a->element_size;
	memcpy(buffer, a->a_dend, a->element_size);
	return 0;
}

void *array_at(ARRAY *a, ssize_t index)
{
	char *p;

	if (a->a_base == NULL) return NULL;
	if (index < 0) {
		p = a->a_dend + (index * a->element_size);
		if (p < a->a_base) return NULL;
	} else {
		p = a->a_base + (index * a->element_size);
		if (p >= a->a_dend) return NULL;
	}
	return p;
}

void array_resize(ARRAY *a, size_t size)
{
	ptrdiff_t end_diff;

	if (a->a_end-a->a_base <= size) {
		end_diff = (size*2)*(a->element_size);
		a->a_base = (char*)realloc(a->a_base, end_diff);
		a->a_end = a->a_base+end_diff;
	}
	
	a->a_dend = a->a_base + (size*a->element_size);
}
