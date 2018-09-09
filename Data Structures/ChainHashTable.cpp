#include "ChainHashTable.h"
#include <random>

ChainHashTable::ChainHashTable() {
	capacity = 0;
	a = nullptr;
}

ChainHashTable::ChainHashTable(int numSlots) {
	capacity = numSlots;
	a = nullptr;
}

ChainHashTable::ChainHashTable(const KVPair *kvPairArray, int kvPairSize, int numSlots, bool limitPrinting) {
	// create our array
	capacity = numSlots;
	a = new ChainNode[capacity];

	// initialize array with -1 to indicate no elements stored
	for (int i = 0; i < capacity; ++i) {
		a[i] = ChainNode();
	}

	// insert keys from array
	for (int i = 0; i < kvPairSize; ++i) {
		insert(kvPairArray[i]);
	}
}

bool ChainHashTable::deleteKey(int key) {
	int hashedKey = hash(key);
	ChainNode *trail = &a[hashedKey];
	ChainNode *node = &a[hashedKey];

	// if first element
	if (trail->getKey() == key) {
		if (trail->getNext() != nullptr) {
			node = node->getNext();

			trail->setValue(node->getValue());
			trail->setKey(node->getKey());
			trail->setNext(node->getNext());

			//delete node;
		} else {
			trail->setKey(-1);
			trail->setNext(nullptr);
		}

		return true;
	} else {
		node = node->getNext();

		while (node != nullptr) {
			if (node->getKey() == key) {
				// remove from list
				trail->setNext(nullptr);

				// remove from meory
				delete node;
				node = nullptr;

				return true;
			} else {
				trail = trail->getNext();
				node = node->getNext();
			}
		}
	}

	return false;
}

int ChainHashTable::search(int key) const {
	int hashedKey = hash(key);
	int steps = 1;
	ChainNode *node = &a[hashedKey];

	while (node != nullptr) {
		if (node->getKey() == key) {
			return steps;
		} else {
			++steps;
			node = node->getNext();
		}
	}

	return -1;
}

void ChainHashTable::insert(KVPair kvPair) {
	int key = kvPair.key;
	int value = kvPair.value;
	int hashedKey = hash(key);

	// check if the index has no current key stored
	ChainNode *node = &a[hashedKey];

	if (node->getKey() == -1) {
		node->setPair(kvPair);
	} else {
		ChainNode *trail = node;
		node = node->getNext();

		// move to the last entry
		while (node != nullptr) {
			node = node->getNext();
			trail = trail->getNext();
		}

		trail->setNext(new ChainNode(kvPair));
	}
}

void ChainHashTable::print() const {
	cout << "Hash table with chaining" << endl
		<< "------------------------" << endl << endl;

	for (int i = 0; i < capacity; ++i) {
		ChainNode *node = &a[i];

		// format the index
		int capacityDigits = 0;
		int capacityCopy = capacity;
		while (capacityCopy / 10 > 0) {
			capacityDigits++;
			capacityCopy = capacityCopy / 10;
		}

		int numSpaces = capacityDigits;
		int j = i;
		while (j / 10 > 0) {
			numSpaces -= 1;
			j = j / 10;
		}

		cout << "Index ";
		while (numSpaces > 0) {
			numSpaces--;
			cout << " ";
		}
		cout << i << ":   ";

		if (node->getKey() != -1) {
			// format and print node if not "empty"

			cout << "(" << node->getKey() << ", " << node->getValue() << ")";
			node = node->getNext();

			while (node != nullptr) {
				cout << " -> (" << node->getKey() << ", " << node->getValue() << ") ";
				node = node->getNext();
			}
		}

		cout << endl;
	}

	cout << endl;
}