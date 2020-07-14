#ifndef DARRAY_TYPE
#define DARRAY_TYPE float
#endif 

#include <stdio.h>
#include "darray.c"

int main(void)
{
	int i, max;
        darray_func darray_f;
	init_darray_func(&darray_f);

        darray* arr = new_darray();
        if (arr == (darray *)MALLOC_FAILED) {
		fprintf(stderr, "MALLOC FAILED!\n");
		return -1;
	}
	
	for(i = 0; i < 25; i++) {
		darray_f.push_back(arr, (float) i);
	}
	
	printf("Last 5 elements\n");
	for(i = 0; i < 5; i++) {
		printf("%f ", darray_f.back(arr));
		darray_f.pop_back(arr);
	}	
	
	printf("\nRemaining elements\n");
	for(i = 0; i < 20; i++) {
		printf("%f ", darray_f.at(arr, i));
	}
	
	destroy_darray(arr);
	return 0;
}	