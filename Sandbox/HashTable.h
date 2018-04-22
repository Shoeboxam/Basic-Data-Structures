
#include <string>

class HashTable {
	std::string mode;
	std::string* table;
	int size;
	int isPrime(int val);
	int nextPrime(int val);
public:
	HashTable(std::string mode, int size);
	~HashTable();
	void insert(std::string input);
};

