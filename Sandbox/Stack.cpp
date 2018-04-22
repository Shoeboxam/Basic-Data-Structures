#include "stdafx.h"
#include <vector>
#include <stdexcept>
#include <string>

#include "Stack.h"

using namespace std;

Stack::Stack() {
	pointer = 0;
}

bool Stack::empty() {
	return pointer < 0;
}

int Stack::pop() {
	if (this->empty()) throw std::out_of_range("There are no items in the stack.");
	pointer--;
	return stack[pointer];
}

void Stack::push(int item) {
	stack.push_back(item);
	pointer++;
}