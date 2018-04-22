#include "stdafx.h"
#include <string>
#include <stdexcept>
#include <iostream>

#include "LinkedList.h"

using namespace std;

template <class T>
Node<T>::Node() {}

template <class T>
Node<T>::Node(int value) : value(value) {}

template <class T>
LinkedList<T>::~LinkedList() {
	Node<T> *temp = this->head;
	while (temp->next != nullptr) {
		Node<T> *nextNode = temp->next;
		delete temp;
		temp = nextNode;
	}
}

template <class T>
Node<T>* LinkedList<T>::findTail(Node<T> *temp) {
	if (temp->next == nullptr) return temp;
	return findTail(temp->next);
}

template <class T>
Node<T>* LinkedList<T>::indexFromNode(Node<T>* tmp, int index) {
	if (index == 0) return tmp;
	if (tmp->next == nullptr) throw std::out_of_range("No index exists.");
	return indexFromNode(tmp->next, index - 1);
}

template <class T>
void LinkedList<T>::prepend(T value) {
	Node<T> *nd = new Node<T>();
	nd->next = this->head;
	nd->value = value;
	this->head = nd;
}

template <class T>
void LinkedList<T>::append(T value) {
	Node<T>* tail = findTail(this->head);

	Node<T>* newNode = new Node<T>();
	newNode->value = value;
	newNode->next = nullptr;

	tail->next = newNode;
}

template <class T>
void LinkedList<T>::insert(T value, int index) {
	if (index == 0) {
		prepend(value);
		return;
	}

	Node<T>* temp = this->indexFromNode(this->head, index - 1);
	Node<T>* newNode = new Node<T>(value);
	newNode->next = temp->next;
	temp->next = newNode;
}


template <class T>
void LinkedList<T>::count(Node<T> *temp, T value) {
	if (temp == nullptr) return 0;
	if (temp->value == value) return count(temp->next) + 1;
	return count(temp->next);
}

template <class T>
Node<T>* LinkedList<T>::findMaxNode(Node<T>* currentNode) {
	if (currentNode->next == nullptr) return currentNode;

	Node<T>* maxNode = findMaxNode(currentNode->next);
	if (maxNode->value > currentNode->value) return maxNode;
	return currentNode;
}

template <class T>
Node<T>* LinkedList<T>::findMaxNodePrior(Node<T>* currentNode) {
	if (currentNode->next == nullptr || currentNode->next->next == nullptr) return currentNode;

	Node<T>* maxNodePrior = findMaxNodePrior(currentNode->next);
	if (maxNodePrior->next->value > currentNode->next->value) return maxNodePrior;
	return currentNode;
}

template <class T>
void LinkedList<T>::selectionSortReversed(Node<T>* priorNode) {

	// Collect the four nodes that need their pointers swapped
	Node<T>* currentNode = priorNode->next;
	if (currentNode->next == nullptr) return;

	Node<T>* maxNodePrior = findMaxNodePrior(priorNode);
	Node<T>* maxNode = maxNodePrior->next;

	// Special case to handle the head
	if (maxNode->value > priorNode->value) {
		maxNodePrior->next = priorNode;
		
		Node<T>* temp = maxNode->next;
		maxNode->next = priorNode->next;
		priorNode->next = temp;

		if (priorNode == this->head) this->head = maxNode;
		priorNode = maxNode;
		currentNode = priorNode->next;

		maxNodePrior = findMaxNodePrior(maxNode);
		maxNode = maxNodePrior->next;
	}

	// Typical case for sorting the next element
	if (maxNode->value > currentNode->value) {
		priorNode->next = maxNode;
		maxNodePrior->next = currentNode;

		Node<T>* temp = maxNode->next;
		maxNode->next = currentNode->next;
		currentNode->next = temp;
	}

	selectionSortReversed(priorNode->next);
}

template <class T>
int LinkedList<T>::length(Node<T>* currentNode) {
	if (currentNode == nullptr) return 0;
	return 1 + this->length(currentNode->next);
}

template <class T>
T* LinkedList<T>::to_array() {
	int length = this->length(this->head);
	T* myArray = new T[length];

	Node<T>* temp = this->head;

	for (int i = 0; i < length; i++) {
		myArray[i] = temp->value;
		temp = temp->next;
	}
	return myArray;
}

template <class T>
std::string LinkedList<T>::to_string(Node<T>* currentNode) {
	if (currentNode->next == nullptr) return std::to_string(currentNode->value);
	return std::to_string(currentNode->value) + " " + LinkedList<T>::to_string(currentNode->next);
};

template <class T>
std::ostream& operator<<(std::ostream &strm, const LinkedList<T> &myList) {
	return strm << LinkedList<T>::to_string(myList.head);
}
