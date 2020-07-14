# Implementing stuff from STL in C

## Frequently Asked Questions
**Am I aware that this is a waste of time?**
Yes

## What am I doing now?
std::vector - see darray.h
So far - push_back, pop_back, front and back have been implemented

## Finished
nothing

## Instructions
The interface of the DS will be in the .h files (public functions in x_func struct)
The implementation will be present in the .c files

Follow any instructions given in the .h files (usually preprocessor macros)
and include the .c files in your program to use them

Or see the x_driver.c file

Generally:
The functions are present in a struct that is **declared** up front (no constructor/destructor)
The members are present in a struct that must be **constructed** and **destructed** using functions