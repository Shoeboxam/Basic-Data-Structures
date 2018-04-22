#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>


template <class T>
class TreeNode {
public:
	T value;
	TreeNode<T> *left = nullptr;
	TreeNode<T> *right = nullptr;
	TreeNode(T value);
};

template <class T>
class BinaryTree {

public:
	TreeNode<T> *root = nullptr;

	void insert(TreeNode<T>* tree, T value);
	static std::string preorder_string(TreeNode<T>* currentNode);
};

template <class T>
std::ostream& operator<<(std::ostream &strm, const BinaryTree<T> &myTree);