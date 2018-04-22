#include "stdafx.h"
#include "HashTable.h"
#include <string>
#include <math.h>


int HashTable::isPrime(int val) {
	for (int i = 2; i < sqrt(val); i++) if (val % i == 0) return false;
	return true;
}

int HashTable::nextPrime(int val){
	while (true) {
		val += 1;
		if (isPrime(val)) return val;
	}
}

HashTable::HashTable(std::string modex, int sizex) {
	table = new std::string[sizex]{ nullptr };
	mode = modex;
	size = sizex;
}

HashTable::~HashTable() {
}

void HashTable::insert(std::string input) {
	int idx = stoi(input) % this->size;

	//if (this->table[idx] == nullptr) {
	//	this->table[idx] = input;
	//}
}
