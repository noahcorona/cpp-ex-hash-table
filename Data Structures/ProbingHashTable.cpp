#include <iostream>
#include "ProbingHashTable.h"

using namespace std;

const int PROBING_METHOD = 1;                       // 1. linear 2. quadratic 3. double hashing
const int INITIAL_CAPACITY = 20;

ostream& operator<<(ostream& out, const ProbingHashTable& printHT) {
	int* HT = printHT.getHT();
	int capacity = printHT.getCapacity();

	for (int i = 0; i < capacity; ++i)
		if (HT[i] != -1)
			cout << "   " << i << ". (" << HT[i] << ")" << endl;
		else
			cout << "   " << i << "." << endl;

	return out;
}

ProbingHashTable::ProbingHashTable() {
	probingMethod = 1;
	capacity = INITIAL_CAPACITY;
	numOfElements = 0;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i) {
		HT[i] = -1;
	}
}

void ProbingHashTable::insertKey(int key) {
	int cycleBegin = (capacity + 1) / 2;
	int j = 0;
	bool inserted = false;
	bool repeated = false;

	while (!inserted && !repeated) {
		int hashedKey = hash(key, j);                // calculate hash

		if (hashedKey != cycleBegin) {               // if at cycle start & not starting
			if (HT[hashedKey] == -1) {               // probe value
				HT[hashedKey] = key;
				inserted = true;                     // insert
			} else
				++j;
		} else {
			if (j == 0) {
				if (HT[hashedKey] == -1) {           // probe value
					HT[hashedKey] = key;
					inserted = true;                 // insert
				} else
					++j;
			} else
				repeated = true;
		}
	}

	// if we completed a cycle finding an open index
	// or we have reached our functional capacity

	if (numOfElements == (capacity * 2) / 3) {

		rehash();

		// insert our key
		j = 0;
		inserted = false;

		while (!inserted) {
			int hashedKey = hash(key, j);           // calculate hash
			if (HT[hashedKey] == -1) {              // probe value
				HT[hashedKey] = key;
				inserted = true;
				++numOfElements;
			} else
				++j;
		}

		system("cls");
		if (numOfElements == (capacity * 2) / 3) cout << "Hit functional capacity or reached a full cycle." << endl << endl;
		cout << "Resized to length: " << capacity << endl << endl;

		system("pause > nul");
		cout << "Press any key to continue...";
	}

	++numOfElements;
}

void ProbingHashTable::rehash() {
	// create new array with next prime
	int newCapacity = nextPrime(capacity * 2);
	int *newArray = new int[newCapacity];
	int cycleBegin = (newCapacity + 1) / 2;

	// initialize new array with -1 values
	for (int i = 0; i < newCapacity; ++i) {
		newArray[i] = -1;
	}

	bool inserted;

	// traverse linearly, rehash, insert
	for (int i = 0; i < capacity; ++i) {
		int j = 0;
		int key = HT[i];
		inserted = false;

		while (!inserted) {
			int hashedKey = hash(key, j);        // calculate hash
			if (newArray[hashedKey] == -1) {     // probe value
				newArray[hashedKey] = key;
				inserted = true;                 // insert
				//numOfElements is unchanged, no need to update
			}
			else
				++j;
		}
	}

	// free old array from memory, reassign
	delete[] HT;
	HT = newArray;
	capacity = newCapacity;
}

// extra functions

ProbingHashTable::ProbingHashTable(int newCapacity) {
	probingMethod = PROBING_METHOD;
	capacity = newCapacity;
	numOfElements = 0;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i) {
		HT[i] = -1;
	}
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, int newCapacity) {
	probingMethod = newProbingMethod;
	capacity = newCapacity;
	numOfElements = 0;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i) {
		HT[i] = -1;
	}
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, int *keyArray, int keyArraySize) {
	probingMethod = newProbingMethod;
	capacity = keyArraySize;
	numOfElements = keyArraySize;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i) {
		HT[i] = -1;
	}

	for (int i = 0; i < keyArraySize; ++i)
		insertKey(keyArray[i]);
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, int *keyArray, int keyArraySize, bool animationsOn) {
	probingMethod = newProbingMethod;
	capacity = keyArraySize;
	numOfElements = keyArraySize;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i) {
		HT[i] = -1;
	}

	for (int i = 0; i < keyArraySize; ++i)
		if (animationsOn)
			insertKeyAnimated(keyArray[i]);
		else
			insertKey(keyArray[i]);
}

int ProbingHashTable::nextPrime(int num) const {
	bool found = false;
	int i = num + 1;   // num is always even
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

int ProbingHashTable::prevPrime(int num) const {
	bool found = false;
	int i = num - 1;
	while (!found) {
		bool prime = true;
		for (int j = 2; j * j < i; ++j) {
			if (i % j == 0)
				prime = false;
		}

		if (prime) found = true;
		else --i;
	}

	return i;
}

void ProbingHashTable::insertKeyAnimated(int key) {
	int cycleBegin = (capacity + 1) / 2;
	int j = 0;
	bool inserted = false;
	bool repeated = false;

	system("cls");
	cout << " Attempting to insert " << key << endl
		<< "------------------------------" << endl << endl;
	for (int i = 0; i < capacity; ++i) {
		if (i == hash(key, 0)) {
			// print key and dont print empty slots
			if (j == (capacity + 1) / 2) {
				cout << "   " << i << ". (" << HT[i] << ")   CYCLE START" << endl;
			}
			else if (HT[i] == -1)
				cout << "   " << i << ". (" << HT[i] << ")   SUCCESS" << endl;
			else
				cout << "   " << i << ". (" << HT[i] << ")   FAIL" << endl;
		}
		else
			if (HT[i] != -1)
				cout << "   " << i << ". (" << HT[i] << ")" << endl;
			else
				cout << "   " << i << ". " << endl;

	}

	while (!inserted && !repeated && numOfElements + 1 < (capacity * 2) / 3) {
		int hashedKey = hash(key, j);                // calculate hash

		if (hashedKey != cycleBegin) {               // if at cycle start & not starting
			if (HT[hashedKey] == -1) {           // probe value
				HT[hashedKey] = key;
				inserted = true;                 // insert
				++numOfElements;
			}
			else
				++j;
		}
		else {
			if (j == 0) {
				if (HT[hashedKey] == -1) {            // probe value
					HT[hashedKey] = key;
					inserted = true;                  // insert
					++numOfElements;
				}
				else
					++j;
			}
			else
				repeated = true;
		}
	}

	bool resized = false;                           // check if we resized

	if (!inserted ||
		repeated ||
		numOfElements == (capacity * 2) / 3) {

		resized = true;

		rehash();

		// insert our key
		j = 0;
		inserted = false;

		while (!inserted) {
			int hashedKey = hash(key, j);           // calculate hash
			if (HT[hashedKey] == -1) {              // probe value
				HT[hashedKey] = key;
				inserted = true;
				++numOfElements;
			}
			else
				++j;
		}

		system("cls");
		if (numOfElements == (capacity * 2) / 3) {
			cout << "Hit functional capacity or reached a full cycle." << endl << endl;
			cout << "Resized to length: " << capacity << endl << endl;
		}
		system("pause > nul");
		cout << "Press any key to continue...";
	}

	system("cls");
	cout << " Attempting to insert " << key << endl
		<< "------------------------------" << endl << endl;
	for (int i = 0; i < capacity; ++i) {
		if (i == hash(key, 0)) {
			// print key and dont print empty slots
			if (j == (capacity + 1) / 2) {
				cout << "   " << i << ". (" << HT[i] << ")   CYCLE START" << endl;
			}
			else if (HT[i] == key)
				cout << "   " << i << ". (" << HT[i] << ")   SUCCESS" << endl;
			else
				cout << "   " << i << ". (" << HT[i] << ")   FAIL" << endl;
		}
		else
			if (HT[i] != -1)
				cout << "   " << i << ". (" << HT[i] << ")" << endl;
			else
				cout << "   " << i << ". " << endl;
	}

	cout << endl << endl << "Press any key to continue...";
	system("pause > nul");
}