#include "stdafx.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "TreeAVL.h"

using namespace std;

template<class T>
NodeAVL<T>::NodeAVL(T value, NodeAVL<T>* parent) : value(value), parent(parent) {}

template<class T>
void TreeAVL<T>::rotateRight(NodeAVL<T>* node1, NodeAVL<T>* node2, NodeAVL<T>* node3) {
	//cout << "Rotating right: " + std::to_string(node1->value) + " " + std::to_string(node2->value) + " " + std::to_string(node3->value) << endl;

	// Correct root if necessary
	if (node1 == this->root) this->root = node2;
	
	// Node one always becomes longer to the right
	node1->offset++;
	// Node two always becomes balanced
	node2->offset = 0;
	
	// ~~~~~ Swap node pointers
	node2->parent = node1->parent;

	if (node1->parent != nullptr) {
		if (node1->parent->right == node1) node1->parent->right = node2;
		else node1->parent->left = node2;
	}

	node1->parent = node2;
	if (node2->right != nullptr) node2->right->parent = node1;

	node1->left = node2->right; // Switch sides, before assigning node2 left
	node2->right = node1;
}

template<class T>
void TreeAVL<T>::rotateLeft(NodeAVL<T>* node1, NodeAVL<T>* node2, NodeAVL<T>* node3) {
	//cout << "Rotating left: " + std::to_string(node1->value) + " " + std::to_string(node2->value) + " " + std::to_string(node3->value) << endl;

	// Correct root if necessary
	if (node1 == this->root) this->root = node2;

	// Node one always becomes longer to the left
	node1->offset--;
	// Node two always becomes balanced
	node2->offset = 0;

	// ~~~~~ Swap node pointers
	node2->parent = node1->parent;

	if (node1->parent != nullptr) {
		if (node1->parent->left == node1) node1->parent->left = node2;
		else node1->parent->right = node2;
	}

	node1->parent = node2;
	if (node2->left != nullptr) node2->left->parent = node1;

	node1->right = node2->left; // Switch sides, before assigning node2 left
	node2->left = node1;
}

template<class T>
NodeAVL<T>* TreeAVL<T>::findSmallest(NodeAVL<T>* currentNode) {
	if (currentNode->left == nullptr) return currentNode;
	return this->findSmallest(currentNode->left);
}

template<class T>
NodeAVL<T>* TreeAVL<T>::findLargest(NodeAVL<T>* currentNode) {
	if (currentNode->right == nullptr) return currentNode;
	return this->findSmallest(currentNode->right);
}

template<class T>
NodeAVL<T>* TreeAVL<T>::findValue(NodeAVL<T>* currentNode, T value) {
	// When the value is not found
	if (currentNode == nullptr) return nullptr;

	if (currentNode->value == value) {
		// return the deepest copy of a repeated number
		if (currentNode->left != nullptr) {
			NodeAVL<T>* temp = findValue(currentNode->left, value);
			if (temp == nullptr) temp = findValue(currentNode->right, value);
			if (temp != nullptr) return temp;
		}
		return currentNode;
	}
	
	// Recurse down subtree
	if (currentNode->value > value) return findValue(currentNode->left, value);
	return findValue(currentNode->right, value);
}

template<class T>
int TreeAVL<T>::height(NodeAVL<T>* currentNode) {
	if (currentNode == nullptr) return 0;
	return max(height(currentNode->left), height(currentNode->right)) + 1;
}

// returns true if length increased. Once it becomes false, it returns without running rebalancing checks
template<class T>
bool TreeAVL<T>::insert(NodeAVL<T>* currentNode, T value) {
	
	if (currentNode == nullptr) {
		this->root = new NodeAVL<T>(value, nullptr);
		return true;
	}

	bool longer = nullptr;
	// Insert to the left (includes when value is same)
	if (value <= currentNode->value) {
		if (currentNode->left == nullptr) {
			//cout << "Insert Left: " << value << endl;
			currentNode->left = new NodeAVL<T>(value, currentNode);
			longer = true;
		}
		else longer = this->insert(currentNode->left, value);
		if (!longer) return false;

		// Handle easy cases first, when insertion does not unbalance tree
		currentNode->offset--;
		if (currentNode->offset == 0) return false;
		if (currentNode->parent == nullptr) return true;  // Root node met, and overall length is longer

		// If parent is not already offset toward currentNode, search further up the tree
		if (currentNode->parent->left == currentNode && currentNode->parent->offset != -1) return true;
		if (currentNode->parent->right == currentNode && currentNode->parent->offset != 1) return true;

		// Left got longer and parent was already offset to the left
		// Check if straight
		if (currentNode == currentNode->parent->left) rotateRight(currentNode->parent, currentNode, currentNode->left);
		else {

			// Correct the zig, then rotate
			NodeAVL<T>* node3 = currentNode->left;
			NodeAVL<T>* node1 = currentNode->parent;
			//cout << "Correcting zig: " << std::to_string(node1->value) + " " + std::to_string(currentNode->value) + " " + std::to_string(node3->value) << endl;

			// ~~~~~ Correct offsets. This is dependent on the state of the third node
			if (node3->offset == 1) {
				currentNode->offset += 1;
				node1->offset -= 1;
			}
			else if (node3->offset == 0) {
				node3->offset = 1;
				currentNode->offset += 1;
			}
			else if (node3->offset == -1) {
				node3->offset = 0;
				currentNode->offset = 1;
			}

			// ~~~~~ Swap node pointers
			node1->right = node3;
			currentNode->parent = node3;
			currentNode->left = node3->right;
			node3->parent = node1;
			if (node3->right != nullptr) node3->right->parent = currentNode;
			node3->right = currentNode;

			// Debug
			//pretty_print(this->root, 0);
			//cout << *this << endl;

			rotateLeft(node1, node3, currentNode);
		}

		return false;
	}

	// Insert to the right
	else {
		if (currentNode->right == nullptr) {
			//cout << "Insert Right: " << value << endl;
			currentNode->right = new NodeAVL<T>(value, currentNode);
			longer = true;
		}
		else longer = this->insert(currentNode->right, value);

		if (!longer) return false;
		currentNode->offset++;
		if (currentNode->offset == 0) return false;
		if (currentNode->parent == nullptr) return true;

		// If parent is not already offset toward currentNode, search further up the tree
		if (currentNode->parent->left == currentNode && currentNode->parent->offset != -1) return true;
		if (currentNode->parent->right == currentNode && currentNode->parent->offset != 1) return true;

		// Right got longer and parent was already offset to the right
		// Check if straight
		if (currentNode == currentNode->parent->right) rotateLeft(currentNode->parent, currentNode, currentNode->right);
		else {
			// Correct the zag, then rotate
			NodeAVL<T>* node3 = currentNode->right;
			NodeAVL<T>* node1 = currentNode->parent;
			//cout << "Correcting zag: " << std::to_string(node1->value) + " " + std::to_string(currentNode->value) + " " + std::to_string(node3->value) << endl;

			// This took significant testing
			if (node3->offset == -1) {
				currentNode->offset -= 1;
				node1->offset += 1;
			}
			else if (node3->offset == 0) {
				node3->offset = -1;
				currentNode->offset -= 1;
			}
			else if (node3->offset == 1) {
				node3->offset = 0;
				currentNode->offset = -1;
			}

			node1->left = node3;
			currentNode->parent = node3;
			currentNode->right = node3->left;
			node3->parent = node1;
			if (node3->left != nullptr) node3->left->parent = currentNode;
			node3->left = currentNode;

			// Debug
			//pretty_print(this->root, 0);
			//cout << *this << endl;
			rotateRight(node1, node3, currentNode);
		}

		return false;
	}
}


template<class T>
void TreeAVL<T>::insert(T value) {
	this->insert(this->root, value);
}

// This function is not part of the assignment, I used it to help visualize the graph as I worked
// Adapted from stack overflow: https://stackoverflow.com/a/13484997
template<class T>
void TreeAVL<T>::pretty_print(NodeAVL<T>* p, int indent)
{
	if (p != nullptr) {
		if (p->right) {
			pretty_print(p->right, indent + 4);
		}
		if (indent) {
			cout << std::setw(indent) << ' ';
		}
		if (p->right) cout << " /\n" << std::setw(indent) << ' ';
		cout << p->value << "\n ";
		if (p->left) {
			cout << std::setw(indent) << ' ' << " \\\n";
			pretty_print(p->left, indent + 4);
		}
	}
}

// Inorder
template<class T>
std::string TreeAVL<T>::to_string_debug(NodeAVL<T>* currentNode) {
	if (currentNode == nullptr) return " ";

	// verify parents are set properly
	if (currentNode->parent != nullptr && currentNode->parent->left != currentNode && currentNode->parent->right != currentNode) {
		return " <PARENT ERROR: " + std::to_string(currentNode->value) + " parent is "+ std::to_string(currentNode->parent->value) + "> ";
	}

	// output both the value and offset, in brackets
	return TreeAVL<T>::to_string(currentNode->left) + "<" + std::to_string(currentNode->value) + " " + std::to_string(currentNode->offset) + ">" + TreeAVL<T>::to_string(currentNode->right);
}

// Inorder
template<class T>
std::string TreeAVL<T>::to_string(NodeAVL<T>* currentNode) {
	if (currentNode == nullptr) return " ";
	return TreeAVL<T>::to_string(currentNode->left) + std::to_string(currentNode->value) + TreeAVL<T>::to_string(currentNode->right);
}

template <class T>
std::ostream& operator<<(std::ostream &strm, const TreeAVL<T> &myTree) {
	return strm << TreeAVL<T>::to_string(myTree.root);
}