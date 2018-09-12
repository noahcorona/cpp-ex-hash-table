#include "ChainHashTable.h"
#include "ProbingHashTable.h"
#include "KVPair.h"
#include "RandomGenerator.h"

using namespace std;

int main() {
	// initialize the range of the keys
	const int KEY_RANGE_LB = 0;
	const int KEY_RANGE_UB = 100;

	// initialize the range of the random values (no affect on anything)
	const int VALUE_RANGE_LB = 0;
	const int VALUE_RANGE_UB = 10;

	// number of pigeons
	const int NUM_KEYS = KEY_RANGE_UB - KEY_RANGE_LB;

	// number of holes (for chaining, num keys != num slots)
	const int NUM_SLOTS = 5;

	// print settings
	// limit (key, value) pair printing to 100, and anything else to 50 lines
	const bool SAFE_PRINTING = false;
	// print out any randomly generated (key, value) pairs
	const bool PRINT_GENERATION = false;

	// generate our randomized input data, store in kvPairArray
	RandomGenerator keyGen = RandomGenerator(KEY_RANGE_LB, KEY_RANGE_UB, VALUE_RANGE_LB, VALUE_RANGE_UB);
	KVPair *kvPairArray = keyGen.keyValueArray;

	if (PRINT_GENERATION) {
		cout << "Randomly generated (key, value) pairs" << endl
			<< "-------------------------------------" << endl;
		for (int i = 0; i < NUM_KEYS; ++i) {
			cout << "   - (" << kvPairArray[i].key << ", " << kvPairArray[i].value << ")" << endl;
		}
		cout << endl << endl;
	}


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
						//cout << "Enter a value: ";
						//cin >> value;

						chainHT.insert(KVPair(stoi(key), 0));
						//chainHT.insert(KVPair(stoi(key), stoi(value)));
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
			ProbingHashTable probingHT;
			bool animationsOn = true;

			system("cls");
			cout << "Hash Table With Probing" << endl
				<< "------------------------" << endl
				<< "1. Generate hash table from random (key, value) pairs" << endl
				<< "2. Generate empty hash table" << endl
				<< "'x' to exit" << endl << endl;

			cin >> inText;

			while (inText != "x") {
				if (inText == "1") {
					system("cls");
					cout << "Animation" << endl
						<< "---------" << endl
						<< "1. Enabled" << endl
						<< "2. Disabled" << endl << endl;
					cin >> inText;

					bool animatedCreate = true;
					if (inText == "2")
						animatedCreate = false;
					system("cls");

					// create empty hash table
					cout << "Enter probing method: " << endl
						<< "1. Linear" << endl
						<< "2. Quadratic" << endl
						<< "3. Double hashing" << endl << endl;
					cin >> inText;
					cout << endl << endl;

					int probingMethod;
					if (inText == "1")
						probingMethod = 1;
					else if (inText == "2")
						probingMethod = 2;
					else if (inText == "3")
						probingMethod = 3;

					// create hash table with probing from kvPairArray
					probingHT = ProbingHashTable(1, kvPairArray, NUM_KEYS, animatedCreate);
				} else if (inText == "2") {
					// create empty hash table
					system("cls");
					cout << "Enter probing method: " << endl
						<< "1. Linear" << endl
						<< "2. Quadratic" << endl
						<< "3. Double hashing" << endl << endl;
					cin >> inText;

					int probingMethod;
					if (inText == "1")
						probingMethod = 1;
					else if (inText == "2")
						probingMethod = 2;
					else if (inText == "3")
						probingMethod = 3;
					
					system("cls");
					cout << "Enter size: ";
					cin >> inText;
					cout << endl << endl;
					probingHT = ProbingHashTable(probingMethod, stoi(inText));
				}

				system("cls");
				cout << "Hash Table With Probing" << endl
					<< "------------------------" << endl
					<< "1. Search for a key" << endl
					<< "2. Delete a key" << endl
					<< "3. Insert a pair" << endl
					<< "4. Print the table" << endl
					<< "5. Toggle Animations (currently: " << (animationsOn ? "on" : "off") << ")" << endl
					<< "'x' to exit" << endl << endl;

				cin >> inText;
				cout << endl;

				while (inText != "x") {
					if (inText == "1") {
						
					} else if (inText == "2") {
						
					} else if (inText == "3") { // insert a (key, value) pair
						
						string key;
						string value;

						cout << endl << "Enter a key: ";
						cin >> key;
						//cout << "Enter a value: ";
						//cin >> value;

						if (animationsOn)
							probingHT.animatedInsert(KVPair(stoi(key), 0));
						else
							probingHT.insert(KVPair(stoi(key), 0));

						inText = "1";
					} else if (inText == "4") {
						probingHT.print();
					} else if (inText == "5") {
						animationsOn = !animationsOn;
					}

					system("cls");
					cout << "Hash Table With Probing" << endl
						<< "------------------------" << endl
						<< "1. Search for a key" << endl
						<< "2. Delete a key" << endl
						<< "3. Insert a pair" << endl
						<< "4. Print the table" << endl
						<< "5. Toggle Animations (currently: " << (animationsOn ? "on" : "off") << ")" << endl
						<< "'x' to exit" << endl << endl;

					cin >> inText;
					cout << endl;
				}
			}
		}
	}

	return 0;
}