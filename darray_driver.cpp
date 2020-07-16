#include <iostream>
#include "darray.h"

using namespace std;

int main(void)
{
	size_t i;
        darray<double> d;
	
	for(i = 0; i < 32; i++) {
		d.push_back(i);
	}
	
	cout << "Last 5 elements\n";
	for(i = 0; i < 5; i++) {
		cout << d.back() << " ";
		d.pop_back();
	}
	
	cout << "\nRemaining elements\n";
	for(i = 0; i < 27; i++) {
		cout << d.at(i) << " ";
	}
	
	cout << "\nThis time using the overloaded operator\n";
	for(i = 0; i < 27; i++) {
		cout << d[i] << " ";
	}
	return 0;
}