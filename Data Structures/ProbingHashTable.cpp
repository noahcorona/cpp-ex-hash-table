#include <iostream>
#include "ProbingHashTable.h"

// for delay
#include <chrono>
#include <thread>

using namespace std;

//for delay
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

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
	numItems = 0;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		HT[i] = -1;
}

int ProbingHashTable::insertKey(int key) {
	bool inserted = false;
	bool cycled = false;
	int j = 0;
	int stepsTaken = 0;

	while (!inserted && !cycled && j < capacity) {
		int hashedKey = hash(key, j);
		
		if (probingMethod == 2 && j >= (capacity + 1) / 2)         // quadratic
			cycled = true;

		if (HT[hashedKey] < 0) {
			HT[hashedKey] = key;
			inserted = true;
		} else
			++j;

		++stepsTaken;
	}

	stepsTaken += j;

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

			++stepsTaken;
		}

		if (j == capacity)
			cerr << "Not good" << endl;
	}

	stepsTaken += j;
	++numItems;

	return stepsTaken;
}

int ProbingHashTable::searchKey(int key) const {
	bool done = false;
	int j = 0;

	while (!done) {
		int hashedKey = hash(key, j);

		if (HT[hashedKey] == -1 ||
			j == (capacity + 1) / 2)
			done = true;
		else if (HT[hashedKey] == key) 
			return j + 1;
		else
			++j;
	}

	return -1;
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
	// create new array with next prime
	int newCapacity = nextPrime(capacity * 2);

	bool inserted = false;
	int *htCopy = HT;
	HT = new int[newCapacity];
	numItems = 0;

	for (int i = 0; i < newCapacity; ++i)
		HT[i] = -1;

	// traverse linearly, rehash, insert
	for (int i = 0; i < capacity; ++i)
		if(htCopy[i] > 0)
			insertKey(htCopy[i]);

	delete[] htCopy;
	capacity = newCapacity;
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

// extra functions

ProbingHashTable::ProbingHashTable(int newCapacity) {
	probingMethod = PROBING_METHOD;
	capacity = newCapacity;
	numItems = 0;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		HT[i] = -1;
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, int newCapacity) {
	probingMethod = newProbingMethod;
	capacity = newCapacity;
	numItems = 0;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		HT[i] = -1;
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, int *keyArray, int keyArraySize) {
	probingMethod = newProbingMethod;
	capacity = keyArraySize;
	numItems = keyArraySize;
	HT = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		HT[i] = -1;

	for (int i = 0; i < keyArraySize; ++i)
		insertKey(keyArray[i]);
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, int *keyArray, int keyArraySize, bool animationsOn) {
	probingMethod = newProbingMethod;
	capacity = keyArraySize;
	numItems = 0;
	HT = new int[capacity];
	int stepsTaken = 0;

	for (int i = 0; i < capacity; ++i)
		HT[i] = -1;

	for (int i = 0; i < keyArraySize; ++i) {

		if (animationsOn)
			stepsTaken += insertKeyAnimated(keyArray[i]);
		else
			stepsTaken += insertKey(keyArray[i]);
	}

	cout << "Inserted " << numItems << " elements in " << stepsTaken << " steps using ";
	if (probingMethod == 1) cout << "linear probing";
	else if (probingMethod == 2) cout << "quadratic probing";
	else if (probingMethod == 3) cout << "double hashing";
	cout << ", final size:" << capacity << endl;

	int searchSteps = 0;
	cout << "Searching for each of the " << keyArraySize << " keys..." << endl;
	for (int i = 0; i < keyArraySize; ++i)
		if (searchKey(keyArray[i]) >= 0)
			searchSteps += searchKey(keyArray[i]);
		//else
		//	cout << "Did not find " << keyArray[i] << endl;

	cout << "Completed in " << searchSteps << " steps" << endl << endl;
}

int ProbingHashTable::nextPrime(int i) const {
	bool found = false;
	++i;   // num is always even
	while (!found) {
		bool prime = true;
		for (int j = 2; j * j < i; ++j)
			if (i % j == 0)
				prime = false;

		if (prime) found = true;
		else ++i;
	}

	return i;
}

int ProbingHashTable::prevPrime(int i) const {
	bool found = false;
	--i;
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

int ProbingHashTable::insertKeyAnimated(int key) {
	bool inserted = false;
	bool cycled = false;
	int j = 0;
	int stepsTaken = 0;

	while (!inserted && !cycled) {
		int hashedKey = hash(key, j);

		if (probingMethod != 2 && j > capacity) {                   // linear or double hash
			cycled = true;
		} else if (probingMethod == 2 && j >= (capacity + 1) / 2)         // quadratic
			cycled = true;

		if (HT[hashedKey] < 0) {
			HT[hashedKey] = key;
			inserted = true;
		} else
			++j;

		++stepsTaken;

		system("cls");
		cout << " Attempting to insert " << key << endl
			<< "------------------------------" << endl << endl;
		for (int i = 0; i < capacity; ++i) {
			if (i == hash(key, j)) {
				// print key and dont print empty slots
				if (j == (capacity + 1) / 2) {
					cout << "   " << i << ". (" << HT[i] << ")   CYCLE START" << endl;
				} else if (HT[i] == key)
					cout << "   " << i << ". (" << HT[i] << ")   SUCCESS" << endl;
				else
					cout << "   " << i << ". (" << HT[i] << ")   FAIL" << endl;
			} else
				if (HT[i] != -1)
					cout << "   " << i << ". (" << HT[i] << ")" << endl;
				else
					cout << "   " << i << ". " << endl;
		}

		sleep_for(5ns);
		sleep_until(system_clock::now() + 5ns);
	}

	stepsTaken += j;

	if (cycled) {
		rehash();
		cout << "Resized to size of " << capacity << endl << endl;

		// wait 1 second
		sleep_for(5ns);
		sleep_until(system_clock::now() + 5ns);

		j = 0;

		while (!inserted) {
			int hashedKey = hash(key, j);

			if (HT[hashedKey] < 0) {
				HT[hashedKey] = key;
				inserted = true;
			} else
				++j;

			++stepsTaken;

			system("cls");
			cout << " Attempting to insert " << key << endl
				<< "------------------------------" << endl << endl;
			for (int i = 0; i < capacity; ++i) {
				if (i == hash(key, j)) {
					// print key and dont print empty slots
					if (HT[i] == key)
						cout << "   " << i << ". (" << HT[i] << ")   SUCCESS" << endl;
					else
						cout << "   " << i << ". (" << HT[i] << ")   FAIL" << endl;
				} else
					if (HT[i] != -1)
						cout << "   " << i << ". (" << HT[i] << ")" << endl;
					else
						cout << "   " << i << ". " << endl;
			}

			sleep_for(5ns);
			sleep_until(system_clock::now() + 5ns);
		}
	}
	stepsTaken += j;
	++numItems;
	return stepsTaken;
}