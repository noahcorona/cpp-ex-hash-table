#include "ChainHashTable.h"
#include "ProbingHashTable.h"
#include "KVPair.h"
#include "RandomGenerator.h"

using namespace std;

int main() {
	// number of holes
	const int NUM_SLOTS = 15;

	// number of pigeons
	const int NUM_KEYS = 30;

	// initialize the range of the random keys
	const int KEY_RANGE_LB = 0;
	const int KEY_RANGE_UB = 42;

	// initialize the range of the random values
	const int VALUE_RANGE_LB = 0;
	const int VALUE_RANGE_UB = 42;

	// print settings
	// limit (key, value) pair printing to 100, and anything else to 50 lines
	const bool SAFE_PRINTING = false;
	// print out any randomly generated (key, value) pairs
	const bool PRINT_RANDOM_GEN = false;

	// generate our randomized input data, store in kvPairArray
	RandomGenerator rng = RandomGenerator(KEY_RANGE_LB, KEY_RANGE_UB, VALUE_RANGE_LB, VALUE_RANGE_UB);
	KVPair kvPairArray[NUM_KEYS];
	if (PRINT_RANDOM_GEN) 
		cout << "Randomly generated (key, value) pairs" << endl
			<< "-------------------------------------" << endl;
	for (int i = 0; i < NUM_KEYS; ++i) {
		int key = rng.getKey();
		int value = rng.getValue();
		kvPairArray[i] = KVPair(key, value);
		if (PRINT_RANDOM_GEN) cout << "   - (" << key << ", " << value << ")" << endl;
	}
	if (PRINT_RANDOM_GEN)  cout << endl << endl;


	cout << "Data Structures" << endl 
		<< "---------------" << endl
		<< "1. Hash table with chaining" << endl 
		<< "2. Hash table with probing" << endl
		<< "Anything else to exit" << endl << endl;

	string inText;
	cin >> inText;
	while (inText == "1" || inText == "2") {
		if (inText == "1") {
			// hash table with chaining
			ChainHashTable chainHT;

			cout << "Hash Table With Chaining" << endl
				<< "------------------------" << endl
				<< "1. Generate hash table from random (key, value) pairs" << endl
				<< "2. Generate empty hash table" << endl
				<< "Anything else to exit" << endl << endl;

			cin >> inText;

			while (inText == "1" || inText == "2") {
				if (inText == "1") {
					// create hash table with chaining from kvPairArray
					chainHT = ChainHashTable(kvPairArray, NUM_KEYS, NUM_SLOTS, SAFE_PRINTING);
				} else if (inText == "2") {
					// create empty hash table
					cout << "Enter size: ";
					cin >> inText;
					cout << endl << endl;
					chainHT = ChainHashTable(stoi(inText));
				}

				cout << "Hash Table With Chaining" << endl
					<< "------------------------" << endl
					<< "1. Search for a key" << endl
					<< "2. Delete a key" << endl
					<< "3. Insert a pair" << endl
					<< "4. Print the table" << endl
					<< "Anything else to exit" << endl << endl;

				cin >> inText;
				cout << endl;

				while (inText == "1" || inText == "2" || inText == "3" || inText == "4") {
					if (inText == "1") {
						// search for a key
						cout << endl << "Enter a key: ";
						string word;
						cin >> word;

						int foundInSteps = chainHT.search(stoi((word)));

						if (foundInSteps != -1) {
							cout << "Found key (" << word << ") in " << foundInSteps << " steps" << endl << endl;
						} else {
							cout << "Key not found. " << endl << endl;
						}
					} else if (inText == "2") {
						// delete a key
						cout << endl << "Enter a key: ";
						string word;
						cin >> word;

						bool deleted = chainHT.deleteKey(stoi(word));

						if (deleted)
							cout << "Deleted key " << word << ".";
						else
							"Key not found.";

						cout << endl << endl;
					} else if (inText == "3") {
						// insert a (key, value) pair

						string key;
						string value;
						
						cout << endl << "Enter a key: ";
						cin >> key;
						cout << "Enter a value: ";
						cin >> value;

						chainHT.insert(KVPair(stoi(key), stoi(value)));
						cout << "Inserted (" + key + ", " + value + ")" << endl;
					} else if (inText == "4") {
						chainHT.print();
					}

					cout << "Hash Table With Chaining" << endl
						<< "------------------------" << endl
						<< "1. Search for a key" << endl
						<< "2. Delete a key" << endl
						<< "3. Insert a pair" << endl
						<< "4. Print the table" << endl
						<< "Anything else to exit" << endl << endl;

					cin >> inText;
					cout << endl;
				}
			}


		} else if (inText == "2") {
			//ProbingHashTable probingHT;
		}
	}

	return 0;
}