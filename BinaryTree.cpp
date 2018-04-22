#include "stdafx.h"
#include <string>
#include <iostream>

#include "BinaryTree.h"

using namespace std;

template <class T>
TreeNode<T>::TreeNode(T value) : value(value) {}


template <class T>
void BinaryTree<T>::insert(TreeNode<T>* tree, T value) {
	if (tree == nullptr) {
		tree = new TreeNode<T>(value);
		return;
	}
	if (value > tree->value) {
		if (tree->left == nullptr) tree->left = new TreeNode<T>(value);
		else this->insert(tree->left, value);
	}
	else {
		if (tree->right == nullptr) tree->right = new TreeNode<T>(value);
		else this->insert(tree->right, value);
	}
}


template <class T>
string BinaryTree<T>::preorder_string(TreeNode<T>* currentNode) {
	if (currentNode == nullptr) return "";
	return std::to_string(currentNode->value) + " " + BinaryTree<T>::preorder_string(currentNode->left) + " " + BinaryTree<T>::preorder_string(currentNode->right);
}


template <class T>
std::ostream& operator<<(std::ostream &strm, const BinaryTree<T> &myTree) {
	return strm << BinaryTree<T>::preorder_string(myTree.root);
}
