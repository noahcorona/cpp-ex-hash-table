#ifndef PROBINGHASHTABLE
#define PROBINGHASHTABLE

using namespace std;

class ProbingHashTable {
public:
	ProbingHashTable();
	ProbingHashTable(int newProbingMethod, int newCapacity);
	ProbingHashTable(int newProbingMethod, int *keyArray, int numKeys, bool limitPrinting);

	void print() const;
	void animatedInsert(int newKey);
	void insert(int newKey);
	int search(int key);
	bool deleteKey(int key);

	~ProbingHashTable() { }
private:
	int* HT;
	int probingMethod;
	int capacity;
	int numOfElements;

	int prevPrime(int num) const;
	int nextPrime(int num) const;

	int hash(int key, int j) {
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

	int secondHash(int k, int q) {
		return 7 - (k % 7);
	}
};

#endif