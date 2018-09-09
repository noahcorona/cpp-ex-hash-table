#ifndef CHAININGNODE
#define CHAININGNODE
#include "KVPair.h"

class ChainNode {

public:
	ChainNode() {
		pair = KVPair(-1, -1); // "empty" slot flag
		next = nullptr;
	}

	ChainNode(KVPair kvPair) {
		pair = kvPair;
		next = nullptr;
	}

	ChainNode(KVPair kvPair, ChainNode* newNext) {
		pair = kvPair;
		next = newNext;
	}

	ChainNode* getNext() const { return next; }
	int getKey() const { return pair.key; }
	int getValue() const { return pair.value; }

	void setPair(KVPair newPair) { pair = newPair; }
	void setNext(ChainNode *newNext) { next = newNext; }
	void setKey(int newKey) { pair.key = newKey; }
	void setValue(int newValue) { pair.value = newValue; }

private:
	KVPair pair;
	ChainNode* next;
};

#endif