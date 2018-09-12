#ifndef PROBINGHASHTABLE
#define PROBINGHASHTABLE

#include "KVPair.h"

using namespace std;

class ProbingHashTable {
public:
	ProbingHashTable();
	ProbingHashTable(int newProbingMethod, int newCapacity);
	ProbingHashTable(int newProbingMethod, KVPair *kvPairArray, int numKeys, bool limitPrinting);

	void print() const;
	void insertPrint(int index, int key) const;
	void animatedInsert(KVPair newPair);
	void insert(KVPair newPair);
	int search(int key);
	bool deleteKey(int key);

	~ProbingHashTable() { }
private:
	KVPair* a;
	int probingMethod;
	int capacity;
	int numOfElements;

	int nextPrime(int num) const;

	int hash(int key, int j) {
		int scrambler = (2 * key) + 5;

		if (probingMethod == 1)
			return (scrambler + j) % capacity;
		else if (probingMethod == 2) 
			return (scrambler + (j * j)) % capacity;
		else 
			return 0;

	}
};

#endif