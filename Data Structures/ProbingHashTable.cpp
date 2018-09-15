#include <iostream>
#include "ProbingHashTable.h"

#include <chrono>                                                  // for delay
#include <thread>                                                  // for delay

using namespace std;

using namespace std::this_thread;                                  // for delay
using namespace std::chrono_literals;                              // for delay
using std::chrono::system_clock;                                   // for delay

const int DEFAULT_PROBING_METHOD = 1;                              // 1. linear 2. quadratic 3. double hashing
const int DEFAULT_INITIAL_CAPACITY = 23;                           // default constructor size

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
	probingMethod = DEFAULT_PROBING_METHOD;
	capacity = DEFAULT_INITIAL_CAPACITY;
	numItems = 0;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		HT[i] = -1;
}

ProbingHashTable::ProbingHashTable(int newProbingMethod) {
	probingMethod = newProbingMethod;
	capacity = DEFAULT_INITIAL_CAPACITY;
	numItems = 0;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		HT[i] = -1;
}

void ProbingHashTable::insertKey(int key) {
	bool inserted = false;
	bool cycled = false;
	int j = 0;

	int hashedKey = hash(key, j);

	while (!inserted && !cycled) {
		int hashedKey = hash(key, j);
		if (j > capacity)
			cycled = true;
		else if (probingMethod == 2 && j >= (capacity + 1) / 2)         // quadratic
			cycled = true;

			if (HT[hashedKey] < 0) {
				HT[hashedKey] = key;
				inserted = true;
			} else
				++j;
	}

	if (cycled) {
		rehash();
		j = 0;

		while (!inserted && j <= capacity) {
			int hashedKey = hash(key, j);

			if (HT[hashedKey] < 0) {
				HT[hashedKey] = key;
				inserted = true;
			} else 
				++j;
		}

		if (j == capacity)
			cerr << "Not good" << endl;
	}

	++numItems;
}

bool ProbingHashTable::searchKey(int key) const {
	bool found = false;
	bool done = false;
	int j = 0;

	while (!found && !done) {
		int hashedKey = hash(key, j);

		if (HT[hashedKey] == key) {
			found = true;
			done = true;
		} else if (HT[hashedKey] == -1)
			done = true;
		else if (probingMethod == 2 && j == (capacity / 2) + 1)
			done = true;
		else if (j > capacity)
			done = true;
		else
			++j;
	}

	return found;
}

bool ProbingHashTable::deleteKey(int key) {
	bool deleted = false;

	int place = searchKey(key);
	if (place != -1) {
		deleted = true;
		HT[place] = -2;
	}

	return deleted;
}

void ProbingHashTable::rehash() {
	int newCapacity = nextPrime(capacity * 2);

	bool inserted = false;
	int *htCopy = new int[capacity];
	for (int i = 0; i < capacity; ++i)
		htCopy[i] = HT[i];
	int oldCapacity = capacity;

	HT = new int[newCapacity];
	numItems = 0;
	capacity = newCapacity;

	for (int i = 0; i < capacity; ++i)
		HT[i] = -1;

	for (int i = 0; i < oldCapacity; ++i)                               // traverse linearly, rehash, insert
		if(htCopy[i] >= 0)
			insertKey(htCopy[i]);

	delete[] htCopy;

}

void ProbingHashTable::resetTable() {
	delete[] HT;
	HT = nullptr;
	numItems = 0;
	capacity = 0;
}

ProbingHashTable& ProbingHashTable::operator=(const ProbingHashTable& copyHT) {
	if (this != &copyHT) {
		delete[] HT;
		numItems = copyHT.numItems;
		capacity = copyHT.capacity;
		HT = new int[capacity];

		for (int i = 0; i < capacity; ++i)
			HT[i] = copyHT.HT[i];
	} else {
		cerr << "Attempted assignment to itself." << endl;
	}

	return *this;
}

int ProbingHashTable::nextPrime(int i) const {
	bool found = false;
	++i;                                                                // num is always even
	while (!found) {
		bool prime = true;
		for (int j = 2; j * j <= i; ++j)
			if (i % j == 0)
				prime = false;

		if (prime)
			found = true;
		else ++i;
	}

	return i;
}

int ProbingHashTable::prevPrime(int i) const {
	bool found = false;
	--i;                                                                // num is always even
	while (!found) {
		bool prime = true;
		for (int j = 2; j * j < i; ++j)
			if (i % j == 0)
				prime = false;

		if (prime) found = true;
		else --i;
	}

	return i;
}

void ProbingHashTable::timedSearch(int *keyArray, int numKeys) const {
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	for (int i = 0; i < numKeys; ++i)
		searchKey(keyArray[i]);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	cout << "Searched for " << numKeys << " keys in " 
		<< chrono::duration_cast<chrono::microseconds>(end - begin).count() 
		<< " microseconds" << endl << endl;
}