#include <iostream>
#include "ProbingHashTable.h"

ProbingHashTable::ProbingHashTable() {
	probingMethod = 1;
	capacity = 0;
	numOfElements = 0;
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, int newCapacity) {
	probingMethod = newProbingMethod;
	capacity = newCapacity;
	numOfElements = 0;
	a = new KVPair[capacity];
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, KVPair *kvPairArray, int kvArraySize, bool animationsOn) {
	probingMethod = newProbingMethod;
	capacity = kvArraySize;
	numOfElements = kvArraySize;
	a = new KVPair[capacity];

	for (int i = 0; i < kvArraySize; ++i)
		if (animationsOn)
			animatedInsert(kvPairArray[i], 1);
		else
			insert(kvPairArray[i], 1);
}

void ProbingHashTable::insert(KVPair pair, int stepSize) {
	int hashedKey = hash(pair.key);

	int j = 0;

	bool inserted = false;
	while (!inserted) {
		if (a[(hashedKey + j) % capacity].key == -1) {
			a[(hashedKey + j) % capacity] = pair;
			inserted = true;
		} else {
			j += stepSize;
		}
	}
}

void ProbingHashTable::animatedInsert(KVPair pair, int stepSize) {
	int hashedKey = hash(pair.key);

	int j = 0;

	bool inserted = false;
	while (!inserted) {
		insertPrint((hashedKey + j) % capacity, pair.key);

		if (a[(hashedKey + j) % capacity].key == -1) {

			// clear console, show insert successful
			a[(hashedKey + j) % capacity] = pair;
			inserted = true;


		} else {
			// clear console, print out proposed insert, and show moving forward if not empty
			j += stepSize;
		}
	}
}


void ProbingHashTable::print() const {
	for (int i = 0; i < capacity; ++i) {
		cout << "   - (" << a[i].key << ", " << a[i].value << ")" << endl;
	}
}

void ProbingHashTable::insertPrint(int index, int key) const {
	system("cls");
	cout << " Attempting to insert " << key << endl
		<< "------------------------------" << endl << endl;

	for (int i = 0; i < capacity; ++i) {
		if (i == index) {
			// print UPDATED key and dont print empty kv pairs
			if (a[i].key == -1)
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")   SUCCESS" << endl;
			else 
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")   FAIL" << endl;
		} else
			if (a[i].key != -1)
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")" << endl;
			else
				cout << "   " << i << ". " << endl;
	}

	cout << endl << endl;
	system("pause");
}