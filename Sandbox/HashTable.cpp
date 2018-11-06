#include "stdafx.h"
#include "HashTable.h"
#include <string>
#include <math.h>


#include <iostream>


HashTable::HashTable(std::string modex, int sizex, int alphabetx, float loadx) {
	table = new std::string[sizex];
	alphabet = alphabetx;
	mode = modex;
	size = sizex;
	load = loadx;
}

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

void HashTable::rehash() {
	int newSize = nextPrime(this->size * 2);
	std::string* newTable = new std::string[newSize];

	std::cout << "Resizing table from " << this->size << " to " << newSize << "." << std::endl;

	for (int i = 0; i < this->size; i++) {
		if (this->table[i] == "") continue;
		this->insert(newTable, newSize, this->table[i]);
	}
	this->size = newSize;
	this->table = newTable;
}

int HashTable::hash(std::string input) {
	int hash = 0;
	int multiplier = 1;

	// compute hash
	for (int i = 0; i < input.length(); i++) {
		hash += ((int)tolower(input[i]) - (int) 'a') * multiplier;
		multiplier *= this->alphabet;
	}
	return hash;
}

int HashTable::probe(std::string * table, int size, std::string input) {
	// get table index
	int idx = abs(this->hash(input)) % size;

	int iteration = 0;
	int offset = 0;

	while (true) {
		if (table[(idx + offset) % size] == "" || table[(idx + offset) % size] == input) return (idx + offset) % size;
		this->collisions++;

		iteration += 1;
		if (this->mode == "linear") offset = iteration;
		if (this->mode == "quadratic") offset = iteration * iteration;
		//std::cout << table[(idx + offset) % size] << std::endl;
	}
}

void HashTable::insert(std::string * table, int size, std::string input) {
	table[this->probe(table, size, input)] = input;
}

void HashTable::insert(std::string input) {
	// insert into table
	this->insert(this->table, this->size, input);
	this->length += 1;

	// resize the table if necessary
	if (this->length / (float) this->size > this->load) this->rehash();
}

bool HashTable::has(std::string input) {
	return this->table[this->probe(this->table, this->size, input)] != "";
}
