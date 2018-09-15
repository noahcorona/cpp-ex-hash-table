#ifndef PROBINGHASHTABLE
#define PROBINGHASHTABLE

using namespace std;

class ProbingHashTable {
	friend ostream& operator<<(ostream& out, const ProbingHashTable& printHT);
public:
	// "standard" functions
	ProbingHashTable();                                            // default constructor
	//ProbingHashTable(const ProbingHashTable& otherHT);             // copy constructor
	//ProbingHashTable(const ProbingHashTable&& otherHT);            // move constructor

	void setHT(int *newHT) { HT = newHT; }                         // mutators
	void setCapacity(int newCapacity) { capacity = newCapacity; }
	int* getHT() const { return HT; }                              // accessors
	int getCapacity() const { return capacity; }

	int insertKey(int key);                                        // returns number of steps taken
	int searchKey(int key) const ;
	bool deleteKey(int key);
	void rehash();
	void resetTable();
	bool isEmpty() const;

	int prevPrime(int num) const;
	int nextPrime(int num) const;

	ProbingHashTable& operator=(const ProbingHashTable& otherHT);  // copy assignment
//	ProbingHashTable& operator=(const ProbingHashTable&& otherHT); // move assignment

	~ProbingHashTable() { }                                        // destructor

	// extra functions for gui
	ProbingHashTable(int newCapacity);
	ProbingHashTable(int *keyArray, int numKeys);
	ProbingHashTable(int newProbingMethod, int newCapacity);
	ProbingHashTable(int newProbingMethod, int *keyArray, int numKeys);
	ProbingHashTable(int newProbingMethod, int *keyArray, int numKeys, bool animationsOn);
	int insertKeyAnimated(int newKey);
private:
	int* HT;
	int probingMethod;
	int capacity;
	int numItems;

	int hash(int key, int j) const {
		int k = key;

		if (probingMethod == 1)
			return (k + j) % capacity;
		else if (probingMethod == 2) 
			return (k + (j * j)) % capacity;
		else if (probingMethod == 3) {
			int q = prevPrime(capacity);
			return (k + j * secondHash(k, q)) % capacity;
		} else {
			exit(0);
		}

	}

	int secondHash(int k, int q) const {                                 // double hash function
		return q - (k % q);
	}

	//int searchKey(int key) const {
	//	return hash(key, 0);
	//} // returns index
};

#endif