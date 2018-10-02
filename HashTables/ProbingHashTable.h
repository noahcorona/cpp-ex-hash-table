#ifndef PROBINGHASHTABLE
#define PROBINGHASHTABLE

using namespace std;

class ProbingHashTable {
	friend ostream& operator<<(ostream& out, const ProbingHashTable& printHT);
public:
	// "standard" functions
	ProbingHashTable();                                            // default constructor
	ProbingHashTable(int newCapacity);
	//ProbingHashTable(const ProbingHashTable& otherHT);             // copy constructor
	//ProbingHashTable(const ProbingHashTable&& otherHT);            // move constructor

	void setHT(int *newHT) { HT = newHT; }                         // mutators
	void setCapacity(int newCapacity) { size = newCapacity; }
	void setProbingMethod(int newProbingMethod) { probingMethod = newProbingMethod; }
	int* getHT() const { return HT; }                              // accessors
	int getCapacity() const { return size; }
	int getProbingMethod() const { return probingMethod; }

	void insertKey(int key);                                        // returns number of steps taken
	bool searchKey(int key) const;
	int stepsBefore(int key) const;                                     // searchKey but returns num of steps to the key
	void timedSearch(int *keyArray, int numKeys) const;
	bool deleteKey(int key);
	void rehash();
	void resetTable();
	bool isEmpty() const;

	int prevPrime(int num) const;
	int nextPrime(int num) const;

	ProbingHashTable& operator=(const ProbingHashTable& otherHT);  // copy assignment
//	ProbingHashTable& operator=(const ProbingHashTable&& otherHT); // move assignment

    ~ProbingHashTable() { delete[] HT; }                                        // destructor
private:
	int* HT;
	int probingMethod;
	int size;
	int numItems;

	int hash(int key, int j) const {
		int k = key;

		if (probingMethod == 1)
			return (k + j) % size;
		else if (probingMethod == 2) 
			return (k + (j * j)) % size;
		else if (probingMethod == 3) {
			int q = prevPrime(size);
			return ((k % size) + j * (q - (k % q))) % size;
		} else {
			exit(0);
		}

	}

	int searchKeyIndex(int key) const;
};

#endif