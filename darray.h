/*
There is a design choice 
1) use void* and let the user write functions that cast to the correct type
for any computation and pass sizeof(type) to us

2) use macros and let the user define the type in their source

This uses the latter.
Any program MUST define DARRAY_TYPE before including darray.h!
*/

/*
This value is used when constructing the dynamic array
*/
#define MINIMUM_SIZE 16

/*
The array will be resized as
(OLD_SIZE * NUMERATOR)/DENOMINATOR + EXTRA
where all 3 are INTEGERS 

Note that this automatically rounds down 
i.e. if NUMERATOR = 3, DENOMINATOR = 2, then SIZE = floor(1.5 * OLD_SIZE) 
automatically

As you can see, I am avoiding having to cast to FP and floor or cast again
*/
#define NUMERATOR 2
#define DENOMINATOR 1
#define EXTRA 0

/* 
Properties/Variables are in darray
Public methods are in darray_func (in the form of function ptrs)

An alternate configuration is to use just one struct, but that wastes memory
as we declare more objects
*/

typedef struct {
	size_t max_size;
	size_t size;
	size_t f_iter;
	size_t r_iter;

	DARRAY_TYPE* data;
}darray;

typedef struct {
	DARRAY_TYPE (*at) (darray*, size_t);
	void (*push_back) (darray*, DARRAY_TYPE);
	void (*pop_back) (darray*);
	DARRAY_TYPE (*front) (darray*);
	DARRAY_TYPE (*back) (darray*);
}darray_func;

/* Initialize the struct with methods */
extern void init_darray_func(darray_func* f);

/* Constructor and destructor for dynamic array */
extern darray* new_darray(void);
extern void destroy_darray(darray* d);
