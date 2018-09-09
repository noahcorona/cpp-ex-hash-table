#ifndef PROBINGHASHTABLE
#define PROBINGHASHTABLE

#include "KVPair.h"

using namespace std;

class ProbingHashTable {
public:
	ProbingHashTable();
	ProbingHashTable(int newProbingMethod, int newCapacity);
	ProbingHashTable(int newProbingMethod, int numKeys, int keyRangeLB, int keyRangeUB, int valueRangeLB, int valueRangeUB);

	void print() const;
	void insert(KVPair newPair);
	void insert(int key, int value);
	void search(int key);
	void deleteKey(int key);

	~ProbingHashTable() { }
private:
	KVPair* a;
	int probingMethod;
	int capacity;
	int numOfElements;

	int hash(int key) {
		return key % capacity;
	}
};

#endif