#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct _array {
	char *a_base, *a_dend, *a_end;
	size_t element_size;
};

typedef struct _array ARRAY;

#define array_clear(A)	((A)->a_dend = (A)->a_base)
#define array_size(A)	(((A)->a_dend - (A)->a_base) / (A)->element_size)

void	array_init(ARRAY *a, size_t element_size);
void	array_destroy(ARRAY *a);

void	array_push(ARRAY *a, const void *data);
int	array_pop(ARRAY *a, void *buffer);
void	*array_at(ARRAY *a, ssize_t index);
void	array_resize(ARRAY *a, size_t size);

#endif
