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
	ChainHashTable(const int *keyArray, int keyArraySize, int numSlots, bool limitPrinting);

	void print() const;
	int search(int key) const;
	void insert(int key);
	bool deleteKey(int key);

	~ChainHashTable() { };
private:
	ChainNode *HT;
	int capacity;

	int hash(int key) const {
		return ((2 * key) + 7) % capacity;
	}
};

#endif