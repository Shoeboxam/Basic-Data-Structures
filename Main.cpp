// Sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <assert.h>

#include "BinaryTree.cpp"
#include "LinkedListDouble.cpp"
#include "LinkedList.cpp"
#include "Stack.h"

using namespace std;


void testStack() {
	Stack myStack;

	for (int i = 0; i < 10; i++) {
		myStack.push(i);
	}

	for (int i = 0; i < 10; i++) {
		cout << myStack.pop() << endl;
	}
}

void testBinaryTree() {

	BinaryTree<int> myTree;

	for (int i = 0; i < 10; i++) {
		myTree.insert(myTree.root, rand() % 100);
	}

	cout << myTree << endl;
}

void testLinkedListDouble() {
	LinkedListDouble<int> myList;

	for (int i = 0; i < 10; i++) {
		myList.append(rand() % 100);
	}

	myList.insert(50, 3);
	cout << myList << endl;

	myList.selectionSort(myList.head);
	cout << myList << endl;
}

template <class T>
int tertiarySearchReversed(T *A, T value, int low, int high) {
	int offset = (high - low) / 3;

	// Base cases: check points of interest
	if (A[low] == value) return low;
	if (A[low + offset] == value) return low + offset;
	if (A[high - offset] == value) return high - offset;
	if (A[high] == value) return high;

	// Return if nothing is found
	if (low >= high) return -1;

	// Recurse down portion of array via indice adjustments
	if (A[low + offset] < value) return tertiarySearchReversed(A, value, low + 1, low + offset - 1);
	if (A[high - offset] > value) return tertiarySearchReversed(A, value, high - offset + 1, high - 1);
	return tertiarySearchReversed(A, value, low + offset + 1, high - offset - 1);
}


void homework1() {
	int length = 30;
	int bound = 100;
	int known_value = rand() % bound;

	int nonexistent_value = rand() % (bound - 1);
	if (nonexistent_value == known_value) nonexistent_value++;

	// Create the initial list without the nonexistent value
	LinkedList<int> myList;
	int i = 0;
	while (i < length - 1) {
		int newValue = rand() % bound;
		if (newValue != nonexistent_value) {
			myList.prepend(newValue);
			i++;
		}
	}

	// Insert the known value at a random spot in the list
	myList.insert(known_value, rand() % (length - 1));

	cout << "Original list: " << myList << endl;

	// Sort the list in reversed order
	myList.selectionSortReversed(myList.head);
	cout << "Sorted list:   " << myList << endl;

	// Convert to an array
	int* myArray = myList.to_array();

	// Find index of the known value
	int known_value_index = tertiarySearchReversed(myArray, known_value, 0, length);

	assert(myArray[known_value_index] == known_value);
	cout << "Known value " << known_value << " is at index " << known_value_index << "." << endl;

	// Find index of non-existent element
	int nonexistent_value_index = tertiarySearchReversed(myArray, nonexistent_value, 0, length);
	assert(nonexistent_value_index == -1);
	cout << "Nonexistent value " << nonexistent_value << " was not found in the array." << endl << endl;
}


int main()
{	
	srand(time(NULL));
	
	for (int i = 0; i < 10; i++) homework1();
	//homework1();
	std::system("pause");
    return 0;
}

