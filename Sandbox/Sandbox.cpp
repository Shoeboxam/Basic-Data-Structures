// Sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Stack {

	std::vector<int> stack;
	int pointer;


public:
	Stack() {
		pointer = 0;
	}

	bool empty() {
		return pointer < 0;
	}

	int pop() {
		if (empty()) throw std::out_of_range("There are no items in the stack.");
		pointer--;
		return stack[pointer];
	}

	void push(int item) {
		stack.push_back(item);
		pointer++;
	}
};

void testStack() {
	Stack myStack;

	for (int i = 0; i < 10; i++) {
		myStack.push(i);
	}

	for (int i = 0; i < 10; i++) {
		std::cout << myStack.pop() << std::endl;
	}
};

template <class T>
class Node {

public:
	T value;
	Node<T> *next = nullptr;
	Node<T> *prev = nullptr;

	Node() {}
	Node(T value) : value(value) {}

	Node<T>* clone() {
		return new Node<T>(*this);
	}
};

template <class T>
class LinkedList {
	Node *head;

	Node* getLast(Node<T> currentNode) {
		if (currentNode.next == nullptr) return currentNode;
		return getLast(currentNode.next);
	}

	void append(T value) {
		Node *lastNode;
		if (head == nullptr) lastNode = this.head;
		else lastNode = getLast(this.head);
		lastNode.next = new Node<T>(value);
	}
};

template <class T>
class DoubleLinkedList {

	Node<T>* findSmallestNode(Node<T>* currentNode) {
		if (currentNode->next == nullptr) return currentNode;

		Node<T>* smallestNode = findSmallestNode(currentNode->next);
		if (smallestNode->value < currentNode->value) return smallestNode;
		return currentNode;
	}

	void swapNodes(Node<T>* node1, Node<T>* node2) {

		if (node1->next == node2) {
			if (node1->prev != nullptr) node1->prev->next = node2;
			if (node2->next != nullptr) node2->next->prev = node1;

			node1->next = node2->next;
			node2->prev = node1->prev;

			node2->next = node1;
			node1->prev = node2;
		}
		else {
			node1->next->prev = node2;
			if (node1->prev != nullptr) node1->prev->next = node2;

			if (node2->next != nullptr) node2->next->prev = node1;
			node2->prev->next = node1;

			Node<T>* temp = node1->next;
			node1->next = node2->next;
			node2->next = temp;

			temp = node1->prev;
			node1->prev = node2->prev;
			node2->prev = temp;
		}
	}

	// Finds Nth neighbor from current node
	Node<T>* indexFromNode(Node<T>* currentNode, int index) {
		if (index == 0) return currentNode;
		if (currentNode->next == nullptr) throw std::out_of_range("There are no items in the stack.");

		if (index < 0) return indexFromNode(currentNode->prev, index + 1);
		return indexFromNode(currentNode->next, index - 1);
	}

public:
	Node<T> *head = nullptr;
	Node<T> *tail = nullptr;

	void insert(T value, int index) {
		Node<T>* leftNode = indexFromNode(this->head, index);
		Node<T>* newNode = new Node<T>(value);

		if (leftNode->next == nullptr) {
			this->tail = newNode;
		}
		else {
			Node<T>* rightNode = leftNode->next;
			rightNode->prev = newNode;
			newNode->next = rightNode;
		}

		newNode->prev = leftNode;
		if (leftNode != nullptr) leftNode->next = newNode;
	}

	void prepend(T value) {
		Node<T>* newNode = new Node<T>(value);
		newNode->next = this->head;
		if (this->head != nullptr) this->head->prev = newNode;
		this->head = newNode;

		if (this->tail == nullptr) this->tail = this->head;
	}

	void append(T value) {
		Node<T>* newNode = new Node<T>(value);
		newNode->prev = this->tail;
		if (this->tail != nullptr) this->tail->next = newNode;
		this->tail = newNode;

		if (this->head == nullptr) this->head = this->tail;
	}

	void selectionSort(Node<T>* currentNode) {
		if (currentNode == nullptr) return;
		if (currentNode->next == nullptr) {
			this->tail = currentNode;
			return;
		}

		Node<T>* smallestNode = findSmallestNode(currentNode);

		// Swap the nodes
		if (smallestNode->value != currentNode->value) {
			swapNodes(currentNode, smallestNode);
		}

		if (currentNode == this->head) this->head = smallestNode;
		if (smallestNode == this->tail) this->tail = currentNode;

		selectionSort(smallestNode->next);
	}

	static string to_string(Node<T>* currentNode) {
		if (currentNode->next == nullptr) return std::to_string(currentNode->value);
		return std::to_string(currentNode->value) + " " + to_string(currentNode->next);
	}
};

template <class T>
ostream& operator<<(std::ostream &strm, const DoubleLinkedList<T> &myList) {
	return strm << DoubleLinkedList<T>::to_string(myList.head);
}

void testLinkedList() {
	DoubleLinkedList<int> myList;

	for (int i = 0; i < 10; i++) {
		myList.prepend(rand() % 100);
	}

	myList.insert(50, 3);
	cout << myList << endl;

	myList.selectionSort(myList.head);
	cout << myList << endl;
}

template <class T>
bool trinarySearch(T *A, T value, int low, int high) {
	for (int i = 0; i < length; i++) {
		cout << A[i] << endl;
	}

	int offset = (low - high) / 3;


	return true;
}


int main()
{	
	//srand(time(NULL));

	//int myList [5] = { 1, 2, 3, 4, 5 };

	//trinarySearch(myList, 2, 5);
	
	testLinkedList();
	system("pause");
    return 0;
}

