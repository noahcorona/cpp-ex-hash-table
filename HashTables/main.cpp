#include <iostream>
#include <random>
#include "ProbingHashTable.h"

#include <chrono>                                                          // for sleep function
#include <thread>                                                          // for sleep function

using namespace std;
using namespace std::this_thread;                                          // for sleep function
using namespace std::chrono_literals;                                      // for sleep function
using std::chrono::system_clock;                                           // for sleep function


const long int NUM_KEYS = 25000;                                          // number of keys used to compare efficiency
                                                                           // of collision resolution methods

void wait() { 
	sleep_for(250ms); 
}

void waitForKeyInput() {
	cout << endl << endl << "Press any key to continue...";
	system("pause > nul");
	system("cls");
}

int main() {
	cout << "1. Comparing collision resolution methods" << endl;           // 1. compare probing methods

	std::random_device random;
	std::mt19937 rng(random());
	std::uniform_int_distribution<> distr(0, NUM_KEYS - 1);

	int *keys = new int[NUM_KEYS];

	for (int i = 0; i < NUM_KEYS; ++i)                                     // generate keys
		keys[i] = i % NUM_KEYS;

	for (int i = 0; i < NUM_KEYS; ++i) {                                   // shuffle keys
		int first = distr(rng);
		int second = distr(rng);
		int temp = keys[first];
		keys[second] = keys[first];
		keys[first] = temp;
	}

	for (int i = 1; i <= 3; ++i) {
		ProbingHashTable probingHT = ProbingHashTable(i);

		cout << endl << "--------------------------------------------------" << endl;
		if (i == 1) cout << "                  Linear probing";
		else if (i == 2) cout << "                 Quadratic probing";
		else if (i == 3) cout << "                  Double hashing";
		cout << endl << "--------------------------------------------------" << endl;
		cout << endl << "Initial size: " << probingHT.getCapacity() << endl;

		for (int j = 0; j < NUM_KEYS; ++j)
			probingHT.insertKey(keys[j]);                                  // 2. test insertKey

		cout << "Final size:   " << probingHT.getCapacity()
			<< endl << endl;

		probingHT.timedSearch(keys, NUM_KEYS);                             // 3. test searchKey
	}

	waitForKeyInput();

	ProbingHashTable probingHT;                                            // 4. test default constructor

	cout << "2. Inserting prime numbers up to 100 with ";
	if (probingHT.getProbingMethod() == 1)
		cout << "linear probing" << endl;
	else if (probingHT.getProbingMethod() == 2)
		cout << "quadratic probing" << endl;
	else if (probingHT.getProbingMethod() == 3)
		cout << "double hashing" << endl;
	int i = 1;
	while (i < 100) {
		system("cls");
		cout << "3. Testing insertKey with prime numbers up to 100 with ";
		if (probingHT.getProbingMethod() == 1)
			cout << "linear probing" << endl;
		else if (probingHT.getProbingMethod() == 2)
			cout << "quadratic probing" << endl;
		else if (probingHT.getProbingMethod() == 3)
			cout << "double hashing" << endl;

		probingHT.insertKey(i);
		cout << probingHT << endl;                                         // 5. test insertion operator
		i = probingHT.nextPrime(i);
		wait();
	}

	i = 97;
	while (i > 0) {
		system("cls");
		cout << "3. Testing deleteKey with prime numbers up to 100 with ";
		if (probingHT.getProbingMethod() == 1)
			cout << "linear probing" << endl;
		else if (probingHT.getProbingMethod() == 2)
			cout << "quadratic probing" << endl;
		else if (probingHT.getProbingMethod() == 3)
			cout << "double hashing" << endl;

		probingHT.deleteKey(i);
		cout << probingHT << endl;                                         // 6. test deleteKey
		i = probingHT.prevPrime(i);
		wait();
	}


	delete[] keys;
	system("pause > nul");
	return 0;
}