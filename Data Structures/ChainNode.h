#ifndef CHAININGNODE
#define CHAININGNODE
#include "KVPair.h"

class ChainNode {

public:
	ChainNode() {
		key = -1; // "empty" slot flag
		next = nullptr;
	}

	ChainNode(int newKey) {
		key = newKey;
		next = nullptr;
	}

	ChainNode(int newKey, ChainNode* newNext) {
		key = newKey;
		next = newNext;
	}

	ChainNode* getNext() const { return next; }
	int getKey() const { return key; }

	void setNext(ChainNode *newNext) { next = newNext; }
	void setKey(int newKey) { key = newKey; }

private:
	int key;
	ChainNode* next;
};

#endif