#pragma once
#include <iostream>

template <class T>
class DoubleNode {

public:
	T value;
	DoubleNode<T> *next = nullptr;
	DoubleNode<T> *prev = nullptr;

	DoubleNode();
	DoubleNode(T value);
};

template <class T>
class LinkedListDouble {

	DoubleNode<T>* findSmallestNode(DoubleNode<T>* currentNode);
	void swapNodes(DoubleNode<T>* node1, DoubleNode<T>* node2);
	DoubleNode<T>* indexFromNode(DoubleNode<T>* currentNode, int index);

public:
	DoubleNode<T> *head = nullptr;
	DoubleNode<T> *tail = nullptr;

	void insert(T value, int index);
	void prepend(T value);
	void append(T value);
	void selectionSort(DoubleNode<T>* currentNode);
	static std::string to_string(DoubleNode<T>* currentNode);
};

template <class T>
std::ostream& operator<<(std::ostream &strm, const LinkedListDouble<T> &myList);
