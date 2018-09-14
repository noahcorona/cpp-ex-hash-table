#include "ChainHashTable.h"
#include "ProbingHashTable.h"
#include "RandomGenerator.h"

using namespace std;

int main() {
	// initialize the range of the keys
	const int KEY_RANGE_LB = 0;
	const int KEY_RANGE_UB = 50;

	// initialize the range of the random values (no affect on anything)
	const int VALUE_RANGE_LB = 0;
	const int VALUE_RANGE_UB = 10;

	// number of pigeons (+ 1 is for the inclusive upper bound)
	const int NUM_KEYS = KEY_RANGE_UB - KEY_RANGE_LB + 1;

	// number of holes (for chaining, num keys != num slots)
	const int NUM_SLOTS = 5;

	// print settings
	// limited printing for large structures
	const bool SAFE_PRINTING = false;
	// print out any generated keys
	const bool PRINT_GENERATION = true;

	// generate our randomized input data, store in key array
	RandomGenerator keyGen = RandomGenerator(KEY_RANGE_LB, KEY_RANGE_UB + 1, VALUE_RANGE_LB, VALUE_RANGE_UB);
	int *keyArray = keyGen.keyArray;

	if (PRINT_GENERATION) {
		cout << "Shuffled keys" << endl
			<< "-------------" << endl;
		for (int i = 0; i < NUM_KEYS; ++i) {
			cout << "  " << i << ". (" << keyArray[i] << ")" << endl;
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
				<< "1. Generate hash table from keys in [" << KEY_RANGE_LB << ", " << KEY_RANGE_UB << "]" << endl
				<< "2. Generate empty hash table" << endl
				<< "Anything else to exit" << endl << endl;

			cin >> inText;

			while (inText == "1" || inText == "2") {
				if (inText == "1") {
					// create hash table with chaining from keyArray
					chainHT = ChainHashTable(keyArray, NUM_KEYS, NUM_SLOTS, SAFE_PRINTING);
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
					<< "3. Insert a key" << endl
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
						// insert a key

						string key;
						
						cout << endl << "Enter a key: ";
						cin >> key;

						chainHT.insert(stoi(key));
						cout << "Inserted (" + key + ")" << endl;
					} else if (inText == "4") {
						chainHT.print();
					}

					cout << "Hash Table With Chaining" << endl
						<< "------------------------" << endl
						<< "1. Search for a key" << endl
						<< "2. Delete a key" << endl
						<< "3. Insert a key" << endl
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
				<< "1. Generate hash table from keys in [" << KEY_RANGE_LB << ", " << KEY_RANGE_UB << "]" << endl
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

					// create hash table with probing from keyArray
					probingHT = ProbingHashTable(1, keyArray, NUM_KEYS, animatedCreate);
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
					<< "3. Insert a key" << endl
					<< "4. Print the table" << endl
					<< "5. Toggle Animations (currently: " << (animationsOn ? "on" : "off") << ")" << endl
					<< "'x' to exit" << endl << endl;

				cin >> inText;
				cout << endl;

				while (inText != "x") {
					if (inText == "1") {                        // search for a key (to do)
						
					} else if (inText == "2") {                 // delete a key (to do)
						
					} else if (inText == "3") {                 // insert a key
						
						string key;
						string value;

						cout << endl << "Enter a key: ";
						cin >> key;

						if (animationsOn)
							probingHT.insertKeyAnimated(stoi(key));
						else
							probingHT.insertKey(stoi(key));

						inText = "1";
					} else if (inText == "4") {                  // print the hash table
						cout << probingHT << endl << endl
							<< "Press any key to continue...";
						system("pause > nul");
					} else if (inText == "5") {                  // toggle animations
						animationsOn = !animationsOn;
					}

					system("cls");
					cout << "Hash Table With Probing" << endl
						<< "------------------------" << endl
						<< "1. Search for a key" << endl
						<< "2. Delete a key" << endl
						<< "3. Insert a key" << endl
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