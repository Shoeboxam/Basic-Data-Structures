#pragma once

#include <vector>


class Stack {

	std::vector<int> stack;
	int pointer;

public:
	Stack();
	bool empty();
	int pop();
	void push(int item);
};