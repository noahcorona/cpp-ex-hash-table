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
	void animatedInsert(KVPair newPair, int steps);
	void insert(KVPair newPair, int steps);
	int search(int key);
	bool deleteKey(int key);

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