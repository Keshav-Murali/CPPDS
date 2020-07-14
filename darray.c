#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "darray.h"

#define MALLOC_FAILED -1

/* Without static, ld looks for another definition and fails to link */
static inline bool in_range(darray *d, size_t index)
{
	if (d->size <= index) {
		return false;
	}

	return true;
}

static inline bool is_empty_darray(darray *d) 
{
	if (d->size == 0) {
		return true;
	}
	
	return false;
}

/*
Since we don't really have exceptions in C, I just close the program in many 
cases
*/
DARRAY_TYPE darray_at(darray* d, size_t index)
{
	if (!in_range(d, index)) {
		fprintf(stderr, "Illegal index accessed!\n");
		exit(EXIT_FAILURE);
	}

	return d->data[index];
}

void darray_auto_realloc(darray* d)
{
	size_t new_size = ((d->max_size * NUMERATOR) / DENOMINATOR) + EXTRA;
	
	/* size_t is unsigned - overflow is likely to create a smaller value */
	if (new_size < d->max_size) {
		fprintf(stderr, "Array too big to track elts if resized!\n");
		exit(EXIT_FAILURE);
	}
	
	d->data = realloc(d->data, new_size);
	
	if (d->data == NULL) {
		fprintf(stderr, "Cannot enlarge array anymore\n");
		exit(EXIT_FAILURE);
	}
	
	d->max_size = new_size;
}

void darray_push_back(darray* d, DARRAY_TYPE t)
{
	if (d->size >= d->max_size) {
		darray_auto_realloc(d);
	}
        
	d->data[d->size] = t;
	d->size++;
}

void darray_pop_back(darray* d)
{
	if (is_empty_darray(d)) {
		fprintf(stderr, "Cannot pop anymore elements\n");
		exit(EXIT_FAILURE);	
	}
        
	d->size--;
}

DARRAY_TYPE darray_front(darray* d)
{
	if (is_empty_darray(d)) {
		fprintf(stderr, "Array is empty!\n");
		exit(EXIT_FAILURE);	
	}
	
	return d->data[0];
}

DARRAY_TYPE darray_back(darray* d)
{
	if (is_empty_darray(d)) {
		fprintf(stderr, "Array is empty!\n");
		exit(EXIT_FAILURE);	
	}
	
	return d->data[d->size - 1];
}

void init_darray_func(darray_func* f) 
{
	f->at = darray_at;
	f->push_back = darray_push_back;
	f->pop_back = darray_pop_back;
	f->back = darray_back;
	f->front = darray_front;
}

darray* new_darray(void)
{
	darray* d = (darray*) malloc(sizeof(darray));
	
	if (d == NULL) {
		return (darray*)MALLOC_FAILED;
	}
	
	d->data = (DARRAY_TYPE*) malloc(sizeof(DARRAY_TYPE) * MINIMUM_SIZE);
	
	if (d->data == NULL) {
		free(d);
		return (darray*)MALLOC_FAILED;
	}
	
	d->f_iter = d->r_iter = d->size = 0;
	d->max_size = MINIMUM_SIZE;
}

void destroy_darray(darray* d)
{
	free(d->data);
	free(d);
}

