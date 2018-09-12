#include <iostream>
#include "ProbingHashTable.h"

int ProbingHashTable::nextPrime(int num) const {
	bool found = false;
	int i = num;
	while (!found) {
		bool prime = true;
		for (int j = 2; j * j < i; ++j) {
			if (i % j == 0)
				prime = false;
		}

		if (prime) found = true;
		else ++i;
	}

	return i;
}

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

	// fill array with/without animations
	for (int i = 0; i < kvArraySize; ++i)
		if (animationsOn)
			animatedInsert(kvPairArray[i]);
		else
			insert(kvPairArray[i]);
}

void ProbingHashTable::insert(KVPair pair) {
	int cycleBegin = (capacity + 1) / 2;
	int j = 0;
	bool inserted = false;
	bool repeated = false;

	while (!inserted && !repeated) {
		int hashedKey = hash(pair.key, j);           // calculate hash

		if (hashedKey != cycleBegin) {               // if at cycle start & not starting
			if (a[hashedKey].key == -1) {            // probe value
				a[hashedKey] = pair;
				inserted = true;                     // insert
			} else
				++j;
		} else {
			if (j == 0) {
				if (a[hashedKey].key == -1) {        // probe value
					a[hashedKey] = pair;
					inserted = true;                 // insert
				} else
					++j;
			} else
				repeated = true;
		}
	}

	if (repeated) {
		// create new array with next prime
		int newCapacity = nextPrime(capacity * 2);
		KVPair *newArray = new KVPair[newCapacity];

		// traverse linearly, rehash, insert
		for (int i = 0; i < capacity; ++i) {
			j = 0;
			inserted = false;

			while (!inserted) {
				int hashedKey = hash(pair.key, j);    // calculate hash
				if (newArray[hashedKey].key == -1) {  // probe value
					newArray[hashedKey] = a[i];
					inserted = true;
				} else
					++j;
			}
		}

		// free old array from memory, reassign
		delete[] a;
		a = newArray;
		capacity = newCapacity;

		// insert our key
		j = 0;
		inserted = false;

		while (!inserted) {
			int hashedKey = hash(pair.key, j);       // calculate hash
			if (a[hashedKey].key == -1) {            // probe value
				a[hashedKey] = pair;
				inserted = true;
			} else
				++j;
		}
	}
}

void ProbingHashTable::animatedInsert(KVPair pair) {
	int cycleBegin = (capacity + 1) / 2;
	int j = 0;
	bool inserted = false;
	bool repeated = false;

	system("cls");
	cout << " Attempting to insert " << pair.key << endl
		<< "------------------------------" << endl << endl;
	for (int i = 0; i < capacity; ++i) {
		if (i == hash(pair.key, 0)) {
			// print UPDATED key and dont print empty kv pairs
			if (j == (capacity + 1) / 2) {
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")   CYCLE START" << endl;
			}
			else if (a[i].key == -1)
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")   SUCCESS" << endl;
			else
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")   FAIL" << endl;
		}
		else
			if (a[i].key != -1)
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")" << endl;
			else
				cout << "   " << i << ". " << endl;

	}

	while (!inserted && !repeated) {
		int hashedKey = hash(pair.key, j);           // calculate hash

		if (hashedKey != cycleBegin) {               // if at cycle start & not starting
				if (a[hashedKey].key == -1) {        // probe value
					a[hashedKey] = pair;
					inserted = true;                 // insert
				} else
					++j;
		} else {
			if (j == 0) {
				if (a[hashedKey].key == -1) {        // probe value
					a[hashedKey] = pair;
					inserted = true;                 // insert
				} else
					++j;
			} else
				repeated = true;
		}
	}

	if (repeated) {
		// create new array with next prime
		int newCapacity = nextPrime(capacity * 2);
		KVPair *newArray = new KVPair[newCapacity];
		
		// traverse linearly, rehash, insert
		for (int i = 0; i < capacity; ++i) {
			j = 0;
			inserted = false;

			while (!inserted) {
				int hashedKey = hash(pair.key, j);    // calculate hash
				if (newArray[hashedKey].key == -1) {  // probe value
					newArray[hashedKey] = a[i];
					inserted = true;
				} else
					++j;
			}
		}

		// free old array from memory, reassign
		delete[] a;
		a = newArray;
		capacity = newCapacity;

		// insert our key
		j = 0;
		inserted = false;

		while (!inserted) {
			int hashedKey = hash(pair.key, j);       // calculate hash
			if (a[hashedKey].key == -1) {            // probe value
				a[hashedKey] = pair;
				inserted = true;
			} else
				++j;
		}
	}

	system("cls");
	cout << " Attempting to insert " << pair.key << endl
		<< "------------------------------" << endl << endl;
	for (int i = 0; i < capacity; ++i) {
		if (i == hash(pair.key, 0)) {
			// print UPDATED key and dont print empty kv pairs
			if (j == (capacity + 1) / 2) {
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")   CYCLE START" << endl;
			}
			else if (a[i].key == pair.key)
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")   SUCCESS" << endl;
			else
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")   FAIL" << endl;
		}
		else
			if (a[i].key != -1)
				cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")" << endl;
			else
				cout << "   " << i << ". " << endl;
	}
	
	cout << endl << endl << "Press any key to continue...";
	system("pause > nul");
}


void ProbingHashTable::print() const {
	for (int i = 0; i < capacity; ++i)
		cout << "   " << i << ". (" << a[i].key << ", " << a[i].value << ")" << endl;

	cout << endl << endl << "Press any key to continue...";
	system("pause > nul");
}

void ProbingHashTable::insertPrint(int index, int key) const {
	
}