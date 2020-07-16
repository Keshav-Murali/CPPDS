#include <iostream>
#include "stack.h"

using namespace std;

int main(void)
{
	size_t i;
        my_stack<int> s;
	
	for(i = 0; i < 56; i++) {
		s.push(i);
	}
	
	cout << "Stack size: " << s.size() << "\n";
	
	cout << "\nElements of the stack are\n";
	for(i = 0; i < 56; i++) {
		cout << s.top() << " ";
		s.pop();
	}
	
	cout << "\nStack size: " << s.size() << "\n";
	return 0;
}