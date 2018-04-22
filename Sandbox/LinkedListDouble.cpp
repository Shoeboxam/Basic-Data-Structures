#include "stdafx.h"
#include <iostream>
#include <string>

#include "LinkedListDouble.h"

using namespace std;


template <class T>
DoubleNode<T>::DoubleNode() {}


template <class T>
DoubleNode<T>::DoubleNode(T value) : value(value) {}


template <class T>
DoubleNode<T>* LinkedListDouble<T>::findSmallestNode(DoubleNode<T>* currentNode) {
	if (currentNode->next == nullptr) return currentNode;

	DoubleNode<T>* smallestNode = findSmallestNode(currentNode->next);
	if (smallestNode->value < currentNode->value) return smallestNode;
	return currentNode;
}


template <class T>
void LinkedListDouble<T>::swapNodes(DoubleNode<T>* node1, DoubleNode<T>* node2) {

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

		DoubleNode<T>* temp = node1->next;
		node1->next = node2->next;
		node2->next = temp;

		temp = node1->prev;
		node1->prev = node2->prev;
		node2->prev = temp;
	}
}

// Finds Nth neighbor from current node
template <class T>
DoubleNode<T>* LinkedListDouble<T>::indexFromNode(DoubleNode<T>* currentNode, int index) {
	if (index == 0) return currentNode;
	if (currentNode->next == nullptr) throw std::out_of_range("There are no items in the stack.");

	if (index < 0) return indexFromNode(currentNode->prev, index + 1);
	return indexFromNode(currentNode->next, index - 1);
}

template <class T>
void LinkedListDouble<T>::insert(T value, int index) {
	DoubleNode<T>* leftNode = indexFromNode(this->head, index);
	DoubleNode<T>* newNode = new DoubleNode<T>(value);

	if (leftNode->next == nullptr) {
		this->tail = newNode;
	}
	else {
		DoubleNode<T>* rightNode = leftNode->next;
		rightNode->prev = newNode;
		newNode->next = rightNode;
	}

	newNode->prev = leftNode;
	if (leftNode != nullptr) leftNode->next = newNode;
}

template <class T>
void LinkedListDouble<T>::prepend(T value) {
	DoubleNode<T>* newNode = new DoubleNode<T>(value);
	newNode->next = this->head;
	if (this->head != nullptr) this->head->prev = newNode;
	this->head = newNode;

	if (this->tail == nullptr) this->tail = this->head;
}

template <class T>
void LinkedListDouble<T>::append(T value) {
	DoubleNode<T>* newNode = new DoubleNode<T>(value);
	newNode->prev = this->tail;
	if (this->tail != nullptr) this->tail->next = newNode;
	this->tail = newNode;

	if (this->head == nullptr) this->head = this->tail;
}

template <class T>
void LinkedListDouble<T>::selectionSort(DoubleNode<T>* currentNode) {
	if (currentNode == nullptr) return;
	if (currentNode->next == nullptr) {
		this->tail = currentNode;
		return;
	}

	DoubleNode<T>* smallestNode = findSmallestNode(currentNode);

	// Swap the nodes
	if (smallestNode->value != currentNode->value) {
		swapNodes(currentNode, smallestNode);
	}

	if (currentNode == this->head) this->head = smallestNode;
	if (smallestNode == this->tail) this->tail = currentNode;

	this->selectionSort(smallestNode->next);
}

template <class T>
std::string LinkedListDouble<T>::to_string(DoubleNode<T>* currentNode) {
	if (currentNode->next == nullptr) return std::to_string(currentNode->value);
	return std::to_string(currentNode->value) + " " + LinkedListDouble<T>::to_string(currentNode->next);
};

template <class T>
std::ostream& operator<<(std::ostream &strm, const LinkedListDouble<T> &myList) {
	return strm << LinkedListDouble<T>::to_string(myList.head);
}