#ifndef RANDOMGENERATOR
#define RANDOMGENERATOR

#include <random>

using namespace std;

class RandomGenerator {
public:
	mt19937 generator;
	uniform_int_distribution<mt19937::result_type> keyRandom;
	uniform_int_distribution<mt19937::result_type> valueRandom;
	int keyRangeLB;
	int keyRangeUB;
	int valueRangeLB;
	int valueRangeUB;
	int *keyArray;
	KVPair *keyValueArray;

	RandomGenerator(int newKeyRangeLB, int newKeyRangeUB, int newValueRangeLB, int newValueRangeUB) {
		keyRangeLB = newKeyRangeLB;
		keyRangeUB = newKeyRangeUB;
		valueRangeLB = newValueRangeLB;
		valueRangeUB = newValueRangeUB;

		int size = keyRangeUB - keyRangeLB;

		// create (key, value) array
		keyValueArray = new KVPair[size];

		for (int i = 0; i < size; ++i) {
			keyValueArray[i].key = i;
			keyValueArray[i].value = getValue();
		}

		for (int i = 0; i < size; ++i)
			shuffleOneRandom(keyValueArray);

		// create key only array
		int *keyArray = new int[size];
		for (int i = 0; i < size; ++i) {
			keyArray[i] = i;
		}

		shuffleOneRandom(keyArray);
	}

private:
	void shuffleOneRandom(int* arr) {
		int firstIndex = getKey();
		int secondIndex = getKey();
		int first = arr[firstIndex];
		int second = arr[secondIndex];
		int temp = second;
		arr[secondIndex] = first;
		arr[firstIndex] = temp;
	}

	void shuffleOneRandom(KVPair* arr) {
		int firstIndex = getKey();
		int secondIndex = getKey();
		int first = arr[firstIndex].key;
		int firstValue = arr[firstIndex].value;
		int second = arr[secondIndex].key;
		int secondValue = arr[secondIndex].value;
		int temp = second;
		int tempValue = secondValue;
		arr[secondIndex].key = first;
		arr[secondIndex].value = firstValue;
		arr[firstIndex].key = temp;
		arr[secondIndex].value = tempValue;
	}

	int getValue() {
		// initialize RNG (using Mersenne Twister)
		generator = mt19937();
		generator.seed(random_device()());
		keyRandom = uniform_int_distribution<mt19937::result_type>(keyRangeLB, keyRangeUB);
		valueRandom = uniform_int_distribution<mt19937::result_type>(valueRangeLB, valueRangeUB);
		return valueRandom(generator);
	}

	int getKey() {
		// initialize RNG (using Mersenne Twister)
		generator = mt19937();
		generator.seed(random_device()());
		keyRandom = uniform_int_distribution<mt19937::result_type>(keyRangeLB, keyRangeUB);
		valueRandom = uniform_int_distribution<mt19937::result_type>(valueRangeLB, valueRangeUB);
		return keyRandom(generator);
	}
};

#endif