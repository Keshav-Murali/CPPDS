#include <iostream>
// I am going to use malloc, realloc and free for only the internal array 
#include <cstdlib>
#include <exception>

// This value is used when constructing the dynamic array
#define MINIMUM_SIZE 8

// Exception messages
#define MALLOC_FAIL "Error: Could not allocate memory for the array!"
#define REALLOC_FAIL "Error: Could not expand the array!"
#define NOT_IN_RANGE "Error: Illegal Index accessed!"
#define TOO_BIG "Error: If resized, array will be too big to be addressed!"
#define ARR_EMPTY "Error: Array does not have any elements!"

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

template <class T>
class darray {
	private:
		std::size_t max_size;
		std::size_t size;
		T* data;
		
		bool in_range(std::size_t index);
		bool is_empty(); 
		void auto_reallocate();
	public:
		darray();
		~darray();
		
		T& at(std::size_t index);
		T& front();
		T& back();
		T& operator[](std::size_t index);
		
	/*	const T& at(std::size_t index) const;
		const T& front() const;
		const T& back() const;
	*/ // Above TBD later - also for operator[]
	
		void push_back(T element);
		void pop_back();
};

// Private member functions
template <class T>
bool darray<T>::in_range(std::size_t index) 
{
	if (this->size <= index) {
		return false;
	}

	return true;
}

template <class T>
bool darray<T>::is_empty() 
{
	if (this->size == 0) {
		return true;
	}

	return false;
}

template <class T>
void darray<T>::auto_reallocate() 
{
	try {
		std::size_t new_size = (((this->max_size * NUMERATOR) / DENOMINATOR) + EXTRA);
		
		/* std::size_t is unsigned - overflow is likely to create a smaller value */
		if (new_size < this->max_size) {
			throw TOO_BIG;
		}
		
		T* temp = (T*) realloc(this->data, new_size * sizeof(T));
		
		if (temp == nullptr) {
			free(this->data);
			throw REALLOC_FAIL;
		}
		
		this->data = temp;
		this->max_size = new_size;
	}
	catch(const char* msg) {
		std::cerr << msg;
		exit(EXIT_FAILURE);
	}	
}

// Constructor and Destructor
template <class T>
darray<T>::darray() 
{
	try {
		this->data = (T*) malloc(sizeof(T) * MINIMUM_SIZE);
		if (this->data == nullptr) {
			throw MALLOC_FAIL;
		}

		this->size = 0;
		this->max_size = MINIMUM_SIZE;

	}
        catch(const char* msg) {
		std::cerr << msg;
		exit(EXIT_FAILURE);
	}
}

template <class T>
darray<T>::~darray() 
{
	free(this->data);
}

// Public member functions
template <class T>
T& darray<T>::at(std::size_t index) 
{
	try {
		if (!in_range(index)) {
			throw NOT_IN_RANGE;
		}
		
		return (this->data[index]);
	}
	catch(const char* msg) {
		std::cerr << msg;
		exit(EXIT_FAILURE);
	}
}

/* Behaviour of front() and back() is undefined on empty containers */
template <class T>
T& darray<T>::front()
{
	try {
		if (is_empty()) {
			throw ARR_EMPTY;
		}
		
		return at(0);
	}
	catch(const char* msg) {
		std::cerr << msg;
		exit(EXIT_FAILURE);
	}
}

template <class T>
T& darray<T>::back()
{
	try {
		if (is_empty()) {
			throw ARR_EMPTY;
		}
		
		return at(this->size - 1);
	}
	catch(const char* msg) {
		std::cerr << msg;
		exit(EXIT_FAILURE);
	}
}

/* Cannot reuse at() since this must NOT perform bounds checking */
template <class T>
T& darray<T>::operator[](std::size_t index)
{
	return this->data[index];
}

template <class T>
void darray<T>::push_back(T element)
{
	if (this->size >= this->max_size) {
		auto_reallocate();
	}
        
	this->data[this->size] = element;
	this->size++;
}

template <class T>
void darray<T>::pop_back()
{
	try {
		if (is_empty()) {
			throw ARR_EMPTY;
		}
		
		this->size--;
	}
	catch(const char* msg) {
		std::cerr << msg;
		exit(EXIT_FAILURE);
	}
}