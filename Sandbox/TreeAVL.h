#pragma once

template <class T>
class NodeAVL {
public:
	NodeAVL<T>* parent = nullptr;
	NodeAVL<T>* left = nullptr;
	NodeAVL<T>* right = nullptr;
	T value;
	int offset = 0;
	NodeAVL(T value, NodeAVL<T>* parent);
};

template <class T>
class TreeAVL {
	void rotateRight(NodeAVL<T>* node1, NodeAVL<T>* node2, NodeAVL<T>* node3);
	void rotateLeft(NodeAVL<T>* node1, NodeAVL<T>* node2, NodeAVL<T>* node3);

	std::string to_string_debug(NodeAVL<T>* currentNode);
	void pretty_print(NodeAVL<T>* p, int indent);

public:
	NodeAVL<T>* root = nullptr;
	NodeAVL<T>* findSmallest(NodeAVL<T>* currentNode);
	NodeAVL<T>* findLargest(NodeAVL<T>* currentNode);
	NodeAVL<T>* findValue(NodeAVL<T>* currentNode, T value);
	int height(NodeAVL<T>* currentNode);

	bool insert(NodeAVL<T>* currentNode, T value);
	void insert(T value);
	static std::string to_string(NodeAVL<T>* currentNode);
};

template <class T>
std::ostream& operator<<(std::ostream &strm, const TreeAVL<T> &myTree);

