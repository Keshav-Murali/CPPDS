#include <iostream>
#include "darray.h"

using namespace std;

int main(void)
{
	size_t i;
        darray<double> d;
	
	for(i = 0; i < 33; i++) {
		d.push_back(i);
	}
	
	cout << "darray size: " << d.size() << "\n";
	cout << "darray capacity: " << d.capacity() << "\n";
	
	cout << "Last 5 elements\n";
	for(i = 0; i < 5; i++) {
		cout << d.back() << " ";
		d.pop_back();
	}
	
	cout << "\ndarray size: " << d.size() << "\n";
	cout << "darray capacity: " << d.capacity() << "\n";
	
	cout << "\nRemaining elements\n";
	for(i = 0; i < 28; i++) {
		cout << d.at(i) << " ";
	}
	
	cout << "\nThis time using the overloaded operator\n";
	for(i = 0; i < 27; i++) {
		cout << d[i] << " ";
	}
	return 0;
}