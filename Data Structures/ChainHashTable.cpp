#include "ChainHashTable.h"
#include <random>

ChainHashTable::ChainHashTable() {
	capacity = 0;
	HT = nullptr;
}

ChainHashTable::ChainHashTable(int numSlots) {
	// create our array
	capacity = numSlots;
	HT = new ChainNode[capacity];
}

ChainHashTable::ChainHashTable(const int *keyArray, int keyArraySize, int numSlots, bool limitPrinting) {
	// create our array
	capacity = numSlots;
	HT = new ChainNode[capacity];

	// initialize array with -1 to indicate no elements stored
	for (int i = 0; i < capacity; ++i) {
		HT[i] = ChainNode();
	}

	// insert keys from array
	for (int i = 0; i < keyArraySize; ++i) {
		insert(keyArray[i]);
	}
}

bool ChainHashTable::deleteKey(int key) {
	int hashedKey = hash(key);
	ChainNode *trail = &HT[hashedKey];
	ChainNode *node = &HT[hashedKey];

	// if first element
	if (trail->getKey() == key) {
		if (trail->getNext() != nullptr) {
			node = node->getNext();

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
	ChainNode *node = &HT[hashedKey];

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

void ChainHashTable::insert(int newKey) {
	int key = newKey;
	int hashedKey = hash(key);

	// check if the index has no current key stored
	ChainNode *node = &HT[hashedKey];

	if (node->getKey() == -1) {
		node->setKey(newKey);
	} else {
		ChainNode *trail = node;
		node = node->getNext();

		// move to the last entry
		while (node != nullptr) {
			node = node->getNext();
			trail = trail->getNext();
		}

		trail->setNext(new ChainNode(key));
	}
}

void ChainHashTable::print() const {
	cout << "Hash table with chaining" << endl
		<< "------------------------" << endl << endl;

	for (int i = 0; i < capacity; ++i) {
		ChainNode *node = &HT[i];

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

			cout << "(" << node->getKey() << ")";
			node = node->getNext();

			while (node != nullptr) {
				cout << " -> (" << node->getKey() << ") ";
				node = node->getNext();
			}
		}

		cout << endl;
	}

	cout << endl;
}