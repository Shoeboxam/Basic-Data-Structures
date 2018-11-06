#include <string>

class HashTable {
	std::string* table;
	std::string mode;

	int size;
	int length = 0;
	int alphabet;
	float load;

	int isPrime(int val);
	int nextPrime(int val);

	void rehash();
	int hash(std::string input);

	void insert(std::string* table, int size, std::string input);
	int probe(std::string* table, int size, std::string input);

public:
	int collisions = 0;

	HashTable(std::string modex, int sizex, int alphabetx, float loadx);
	void insert(std::string input);
	bool has(std::string input);
};
