// For now, this uses vector. Will be refactored after I implement forward_list
#include <iostream>
#include "darray.h"

template <class T>
class my_stack {
	private:
		darray<T> array;
	public:
		bool empty();
		std::size_t size();
		T& top();
		void push(const T&);
		void pop();
};

// For now, no constructor or destructor seems necessary

template <class T>
bool my_stack<T>::empty() 
{
	return array.empty();
}

template <class T>
std::size_t my_stack<T>::size()
{
	return array.size();
}

template <class T>
T& my_stack<T>::top()
{
	return array.back();
}

template <class T>
void my_stack<T>::push(const T& element)
{
	array.push_back(element);
}

template <class T>
void my_stack<T>::pop()
{
	array.pop_back();
}