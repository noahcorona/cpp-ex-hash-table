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

ProbingHashTable::ProbingHashTable(const ProbingHashTable& otherHT) {
	
}

void ProbingHashTable::insert(KVPair pair) {
	int cycleBegin = (capacity + 1) / 2;
	int j = 0;
	bool inserted = false;
	bool cycled = false;

	while (!inserted) {
		if (j == cycleBegin) {
			if (!cycled) {
				cycled = true;
			} else {
				// create new array
				//delete[] a;
				
				// double capacity
				int newCapacity = capacity * 2;
				// increment by 1 (evens are never prime)
				++newCapacity;

				bool isPrime = true;
				while (!isPrime) {
					for (int i = 2; i * i < newCapacity; ++i) {
						if (newCapacity % i == 0) {
							isPrime = false;
							break;
						}
					}

					if (!isPrime) ++newCapacity;
				}

				cout << "New size (prime) is: " << newCapacity << endl;
				cout << endl;
				system("pause > nul");
				exit(0);
			}
		} else {
			// calculate hash
			int hashedKey = hash(pair.key, j);
			if (a[hashedKey].key == -1) {
				a[hashedKey] = pair;
				inserted = true;
			} else {
				++j;
			}
		}
	}
}

void ProbingHashTable::animatedInsert(KVPair pair) {
	int j = 0;
	bool inserted = false;

	while (!inserted) {
		// calculate hash
		int hashedKey = hash(pair.key, j);

		// key after hash, and key before hash
		insertPrint(hashedKey, pair.key);

		if (a[hashedKey].key == -1) {
			// clear console, show insert successful
			a[hashedKey] = pair;
			inserted = true;
		} else {
			// clear console, print out proposed insert, and show moving forward if not empty
			++j;
		}
	}

	system("pause > nul");
}


void ProbingHashTable::print() const {
	for (int i = 0; i < capacity; ++i)
		cout << "   - (" << a[i].key << ", " << a[i].value << ")" << endl;
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