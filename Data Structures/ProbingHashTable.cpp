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

ProbingHashTable::ProbingHashTable() {
	probingMethod = 1;
	capacity = 0;
	numOfElements = 0;
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

ProbingHashTable::ProbingHashTable(int newProbingMethod, int *keyArray, int keyArraySize, bool animationsOn) {
	probingMethod = newProbingMethod;
	capacity = keyArraySize;
	numOfElements = keyArraySize;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i) {
		HT[i] = -1;
	}

	// fill array with/without animations
	for (int i = 0; i < keyArraySize; ++i)
		if (animationsOn)
			animatedInsert(keyArray[i]);
		else
			insert(keyArray[i]);
}

void ProbingHashTable::insert(int key) {
	int cycleBegin = (capacity + 1) / 2;
	int j = 0;
	bool inserted = false;
	bool repeated = false;

	while (!inserted && !repeated) {
		int hashedKey = hash(key, j);                // calculate hash

		if (hashedKey != cycleBegin) {               // if at cycle start & not starting
			if (HT[hashedKey] == -1) {                // probe value
				HT[hashedKey] = key;
				inserted = true;                     // insert
			} else
				++j;
		} else {
			if (j == 0) {
				if (HT[hashedKey] == -1) {            // probe value
					HT[hashedKey] = key;
					inserted = true;                 // insert
				} else
					++j;
			} else
				repeated = true;
		}
	}

	if (!inserted || repeated) {
		// create new array with next prime
		int newCapacity = nextPrime(capacity * 2);
		int *newArray = new int[newCapacity];

		// traverse linearly, rehash, insert
		for (int i = 0; i < capacity; ++i) {
			j = 0;
			inserted = false;

			while (!inserted) {
				int hashedKey = hash(key, j);       // calculate hash
				if (newArray[hashedKey] == -1) {    // probe value
					newArray[hashedKey] = HT[i];
					inserted = true;
				} else
					++j;
			}
		}

		// free old array from memory, reassign
		delete[] HT;
		HT = newArray;
		capacity = newCapacity;

		// insert our key
		j = 0;
		inserted = false;

		while (!inserted) {
			int hashedKey = hash(key, j);          // calculate hash
			if (HT[hashedKey] == -1) {              // probe value
				HT[hashedKey] = key;
				inserted = true;
			} else
				++j;
		}
	}
}

void ProbingHashTable::animatedInsert(int key) {
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

	while (!inserted && !repeated) {
		int hashedKey = hash(key, j);                // calculate hash

		if (hashedKey != cycleBegin) {               // if at cycle start & not starting
				if (HT[hashedKey] == -1) {            // probe value
					HT[hashedKey] = key;
					inserted = true;                 // insert
				} else
					++j;
		} else {
			if (j == 0) {
				if (HT[hashedKey] == -1) {            // probe value
					HT[hashedKey] = key;
					inserted = true;                 // insert
				} else
					++j;
			} else
				repeated = true;
		}
	}

	if (!inserted || repeated) {
		// create new array with next prime
		int newCapacity = nextPrime(capacity * 2);
		int *newArray = new int[newCapacity];
		
		for (int i = 0; i < newCapacity; ++i) {
			newArray[i] = -1;
		}

		// traverse linearly, rehash, insert
		for (int i = 0; i < capacity; ++i) {
			j = 0;
			inserted = false;

			while (!inserted) {
				int hashedKey = hash(key, j);     // calculate hash
				if (newArray[hashedKey] == -1) {  // probe value
					newArray[hashedKey] = HT[i];
					inserted = true;
				} else
					++j;
			}
		}

		// free old array from memory, reassign
		delete[] HT;
		HT = newArray;
		capacity = newCapacity;

		// insert our key
		j = 0;
		inserted = false;

		while (!inserted) {
			int hashedKey = hash(key, j);            // calculate hash
			if (HT[hashedKey] == -1) {            // probe value
				HT[hashedKey] = key;
				inserted = true;
			} else
				++j;
		}
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


void ProbingHashTable::print() const {
	for (int i = 0; i < capacity; ++i)
		cout << "   " << i << ". (" << HT[i] << ")" << endl;

	cout << endl << endl << "Press any key to continue...";
	system("pause > nul");
}