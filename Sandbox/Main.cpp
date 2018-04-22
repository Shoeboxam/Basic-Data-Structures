
#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <assert.h>
#include <cstdlib>
#include <utility>
#include <fstream>

#include "BinaryTree.cpp"
#include "LinkedListDouble.cpp"
#include "LinkedList.cpp"
#include "TreeAVL.cpp"
#include "Stack.h"

#include "HashTable.cpp"

using namespace std;
#define LENGTH 5

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

void homework2() {
	// # elements to add to tree
	long int length = 100000;

	// inputs restricted to interval: [0, bound)
	long int bound = RAND_MAX;

	TreeAVL<int> myTree;
	//int zigCase1[] = { 88, 29, 64 };
	//int zigCase2[] = { 88, 29, 64, 19, 34, 63 };
	//int zigCase3[] = { 88, 29, 64, 19, 34, 33 };

	for (int i = 0; i < length; i++) {
		//myTree.insert(zigCasex[i]);
		myTree.insert(rand() % bound);
	}

	int lastValue = rand() % bound;
	myTree.insert(lastValue);
	NodeAVL<int>* lastNode = myTree.findValue(myTree.root, lastValue);

	//cout << "Inorder traversal: " << myTree << endl;
	cout << length << " nodes in the interval [0, " << bound << ")" << endl;
	cout << "Last inserted value: " << lastValue << endl;

	// I implemented the AVL tree using balance factors. 
	// The benefit of balance factors is that an AVL tree may be constructed using only two additional bits of memory overhead compared to a binary search tree.
	// I still use the algorithm discussed in class, but I have to fiddle with offsets instead of heights.

	// Unfortunately, this means heights aren't stored in the nodes, so I must compute heights here in the validation.
	while (lastNode != nullptr) {
		cout << "<" << lastNode->value << ">" << " Left height: " << myTree.height(lastNode->left) << " Right height: " << myTree.height(lastNode->right) << endl;
		lastNode = lastNode->parent;
	}
	cout << endl;
}

// Turns the array into a max heap
void heapify(int myArray[], int length) {

	// heap will consume the array
	for (int lastElement = 0; lastElement < length; lastElement++) {

		// percolate the last element up to heapify
		int depth = lastElement;
		while (depth != 0 && myArray[depth] > myArray[depth / 2]) {
			int temp = myArray[depth];
			myArray[depth] = myArray[depth / 2];
			myArray[depth / 2] = temp;

			depth /= 2;
		}
	}
}

// max value moved to head
void percolate_down(int myArray[], int length) {
	int depth = 0;

	// must replace current node with max child as root node percolates down
	int maxChild;

	while (depth < length) {

		// cannot percolate deeper
		if (depth * 2 > length) return;

		// only one child, so it must be max
		if (depth * 2 + 1 > length) maxChild = depth * 2;

		// take the max of its two children
		else {
			if (myArray[depth * 2] > myArray[depth * 2 + 1]) maxChild = depth * 2;
			else maxChild = depth * 2 + 1;
		}

		// node has percolated such that its children are smaller
		if (myArray[maxChild] < myArray[depth]) return;

		// swap with larger child
		int temp = myArray[depth];
		myArray[depth] = myArray[maxChild];
		myArray[maxChild] = temp;

		// repeat for next layer of heap
		depth = maxChild;
	}
}

// under the assumption of max heap
void heapSort(int myArray[], int length) {
	// swap max element with the final child, shrink the heap and percolate
	for (int lastElement = length; lastElement > 0; lastElement--) {
		int temp = myArray[lastElement - 1];
		myArray[lastElement - 1] = myArray[0];
		myArray[0] = temp;

		// percolate up to last array element by subtracting two: 
		// once to correct for zero-base, the other to make smaller
		percolate_down(myArray, lastElement - 2);
	}
}

void homework3() {
	int length = 15;
	int myArray[15];

	// PART A [random array]
	for (int i = 0; i < length; i++) {
		myArray[i] = rand() % 100;
		cout << "[" << i << ": " << myArray[i] << "] ";
	}
	cout << endl;

	// PART B [heapify]
	heapify(myArray, length);
	for (int i = 0; i < length; i++) {
		cout << "[" << i << ": " << myArray[i] << "] ";
	}
	cout << endl;

	// PART C [heap sort]
	heapSort(myArray, length);
	for (int i = 0; i < length; i++) {
		cout << "[" << i << ": " << myArray[i] << "] ";
	}
	cout << endl;

	// random unit test
	for (int i = 0; i < length - 1; i++) {
		if (myArray[i] > myArray[i + 1]) throw new std::exception("Array is not ordered!");
	}
}

void graphDepthFirst(bool graph[][LENGTH], int node, int traversal[]) {

	// end traversal early if all nodes have been traversed
	if (traversal[0] == LENGTH) return;

	// check if node has been traversed
	for (int i = 1; i <= LENGTH + 1; i++) if (traversal[i] == node) return;

	// add node to traversal
	traversal[0] = traversal[0] + 1;
	traversal[traversal[0]] = node;

	// traverse all neighbors
	for (int i = 0; i < LENGTH; i++) {
		if (graph[node][i]) graphDepthFirst(graph, i, traversal);
	}
}

class QueueNode {
public:
	int value;
	QueueNode *next = nullptr;
	QueueNode(int value) : value(value) {};
};

class Queue {
public:
	QueueNode *head = nullptr;

	int dequeue() {
		QueueNode *headNode = this->head;
		this->head = head->next;

		int value = headNode->value;
		delete headNode;
		return value;
	};

	void enqueue(int val) {
		QueueNode *temp = this->head;

		if (temp == nullptr) {
			this->head = new QueueNode(val);
			return;
		}

		if (temp->value == val) return;

		while (temp->next != nullptr) {
			temp = temp->next;
			if (temp->value == val) return;
		}
		temp->next = new QueueNode(val);
	}
};

void graphBreadthFirst(bool graph[][LENGTH], int node, int traversal[]) {

	Queue nodeQueue;
	nodeQueue.enqueue(node);

	while (nodeQueue.head != nullptr) {
		int node = nodeQueue.dequeue();

		traversal[0]++;
		traversal[traversal[0]] = node;

		// check all nodes...
		for (int i = 0; i < LENGTH; i++) {
			// ...and if node is neighbor...
			if (graph[node][i] && i != node) {
				// ...then check if it has already been traversed
				bool isTraversed = false;
				for (int j = 1; j <= traversal[0]; j++) if (traversal[j] == i) isTraversed = true;

				// traverse the node and add to queue (if the queue doesn't already have it)
				if (!isTraversed) nodeQueue.enqueue(i);
			}
		}
	}
}

void homework4() {
	bool myGraph[LENGTH][LENGTH];

	// header formatting
	cout << "    ";
	for (int i = 0; i < LENGTH; i++) cout << i << " ";
	cout << endl << "   ";
	for (int i = 0; i < LENGTH * 2; i++) cout << "_";

	// create/print a random graph
	for (int i = 0; i < LENGTH; i++) {
		cout << endl << i << " | ";
		for (int j = 0; j < LENGTH; j++) {
			myGraph[i][j] = 0 == rand() % 2;
			cout << myGraph[i][j] << ' ';
		}
	}

	// start at a random node
	int startNode = rand() % LENGTH;

	// BEGIN DFS
	// store traversal in an array. The first index records number of elements traversed
	int* traversal = new int[LENGTH + 1];
	traversal[0] = 0;
	for (int i = 1; i < LENGTH + 1; i++) traversal[i] = -1;

	// edit the traversal array in-place
	graphDepthFirst(myGraph, startNode, traversal);

	// this is enabled if the tree is not spanning
	bool isComplete = true;

	cout << endl << "DEPTH-FIRST TRAVERSAL from " << startNode << endl;
	for (int i = 1; i < LENGTH + 1; i++) {
		if (traversal[i] != -1) cout << traversal[i] << ' ';
		else isComplete = false;
	}

	if (!isComplete) {
		cout << endl << "DISCONNECTED ELEMENTS: ";
		for (int i = 0; i < LENGTH; i++) {
			bool isConnected = false;
			for (int j = 1; j < LENGTH + 1; j++) if (traversal[j] == i) isConnected = true;
			if (!isConnected) cout << i << " ";
		}
		cout << endl;
	}

	// BEGIN BFS
	// store traversal in an array. The first index records number of elements traversed
	traversal[0] = 0;
	for (int i = 1; i < LENGTH + 1; i++) traversal[i] = -1;

	// edit the traversal array in-place
	graphBreadthFirst(myGraph, startNode, traversal);

	// this is enabled if the tree is not spanning
	isComplete = true;

	cout << endl << endl << "BREADTH-FIRST TRAVERSAL from " << startNode << endl;
	for (int i = 1; i < LENGTH + 1; i++) {
		if (traversal[i] != -1) cout << traversal[i] << ' ';
		else isComplete = false;
	}

	if (!isComplete) {
		cout << endl << "DISCONNECTED ELEMENTS: ";
		for (int i = 0; i < LENGTH; i++) {
			bool isConnected = false;
			for (int j = 1; j < LENGTH + 1; j++) if (traversal[j] == i) isConnected = true;
			if (!isConnected) cout << i << " ";
		}
		cout << endl;
	}

	cout << endl;
}

class Edge {
public:
	int target;
	int weight;

	Edge() {};
	
	Edge(int tgt, int wgt) : target(tgt), weight(wgt) {};
};


bool BellmanFord(LinkedList<Edge> myGraph[LENGTH], int distance[LENGTH], int parent[LENGTH]) {
	for (int i = 0; i < LENGTH; i++) {
		distance[i] = 0;
		parent[i] = -1;
	}
	parent[0] = 0;

	// iterate until final round
	for (int round = 1; round <= LENGTH; round++) {
		bool hasChange = false;
		//cout << "Round " << round << endl;

		// loop through edges
		for (int src = 0; src < LENGTH; src++) {
			Node<Edge>* temp = myGraph[src].head;

			// skip ahead when the source node hasn't been reached yet
			if (parent[src] == -1) continue;

			while (temp != nullptr) {

				int tgt = temp->value.target;
				int wgt = temp->value.weight;

				temp = temp->next;
				//cout << "<" << src << " " << tgt << " | " << wgt << ">" << endl;

				if (parent[tgt] == -1 || distance[tgt] > distance[src] + wgt) {
					if (round == LENGTH) return false;
					hasChange = true;

					distance[tgt] = distance[src] + wgt;
					parent[tgt] = src;
				}
			}
		}
		if (!hasChange) return true;
	}
	return true;
}


void homework5() {
	// implement Bellman Ford algorithm to find shortest path
	LinkedList<Edge> myGraph[LENGTH];

	// s t x y z
	// 0 1 2 3 4
	myGraph[0].prepend(Edge(1, +6));  // s->t = 6
	myGraph[0].prepend(Edge(3, +7));  // s->y = 7
	myGraph[1].prepend(Edge(2, +5));  // t->6 = 6
	myGraph[1].prepend(Edge(3, +8));  // t->y = 8
	myGraph[1].prepend(Edge(4, -5));  // t->z = 5
	myGraph[2].prepend(Edge(1, -2));  // x->t = -2
	myGraph[3].prepend(Edge(4, +9));  // y->z = 9
	myGraph[3].prepend(Edge(2, -3));  // y->x = -3
	myGraph[4].prepend(Edge(2, +7));  // z->x = 7
	myGraph[4].prepend(Edge(0, +2));  // z->s = 2

	// if parent is -1, then distance is INF
	string label[LENGTH] = { "S", "T", "X", "Y", "Z" };
	int distance[LENGTH];
	int parent[LENGTH];

	cout << "--- CASE 1 ---" << endl;
	if (BellmanFord(myGraph, distance, parent)) {
		cout << "Shortest routes found: " << endl;
		for (int i = 0; i < LENGTH; i++) {
			cout << "<" << i << " " << parent[i] << " " << distance[i] << ">" << endl;
		}
	}
	else cout << "Negative cycle found!" << endl;
	
	cout << endl << "--- CASE 2 ---" << endl;
	myGraph[3].head->value.weight = -2;

	if (BellmanFord(myGraph, distance, parent)) {
		cout << "Shortest route found: " << endl;
		for (int i = 0; i < LENGTH; i++) {
			cout << "Vertex: " << label[i] << " Parent: " << label[parent[i]] << " Distance: " << distance[i] << endl;
		}
	}
	else cout << "Negative cycle found!" << endl;
}

void homework6() {
	string line;
	ifstream myfile("word_list.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cout << line << '\n';
		}
		myfile.close();
	}
	
	HashTable* table = new HashTable("linear", 2);
}


int main()
{	
	srand(time(NULL));
	homework6();
    return 0;
}

