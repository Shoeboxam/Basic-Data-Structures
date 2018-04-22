#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>


template <class T>
class Node {
public:
	T value;
	Node<T> *next = nullptr;
	
	Node();
	Node(int value);
};

template <class T>
class LinkedList {
public:
	~LinkedList();
	Node<T>* head = nullptr;
	Node<T>* findTail(Node<T> *tmp);
	Node<T>* indexFromNode(Node<T>* tmp, int index);
	void prepend(T value);
	void append(T value);
	void insert(T value, int index);
	void count(Node<T> *tmp, T value);
	Node<T>* findMaxNode(Node<T>* currentNode);
	Node<T>* findMaxNodePrior(Node<T>* currentNode);
	void selectionSortReversed(Node<T>* currentNode);
	int length(Node<T>* currentNode);
	T * to_array();
	static std::string to_string(Node<T>* currentNode);
};

template <class T>
std::ostream& operator<<(std::ostream &strm, const LinkedList<T> &myList);
