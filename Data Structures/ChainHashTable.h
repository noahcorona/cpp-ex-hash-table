#ifndef CHAINHASHTABLE
#define CHAINHASHTABLE

#include <string>
#include <iostream>
#include "ChainNode.h"
#include "KVPair.h"

using namespace std;

class ChainHashTable {
public:
	ChainHashTable();
	ChainHashTable(int numSlots);
	ChainHashTable(const KVPair *kvPairArray, int kvPairsize, int numSlots, bool limitPrinting);

	void print() const;
	int search(int key) const;
	void insert(KVPair kvPair);
	bool deleteKey(int key);

	~ChainHashTable() { };
private:
	ChainNode *a;
	int capacity;

	int hash(int key) const {
		return key % capacity;
	}
};

#endif