#ifndef RANDOMGENERATOR
#define RANDOMGENERATOR

#include <random>

using namespace std;

class RandomGenerator {
public:
	mt19937 generator;
	uniform_int_distribution<mt19937::result_type> keyRandom;
	int keyRangeLB;
	int keyRangeUB;
	int valueRangeLB;
	int valueRangeUB;
	int *keyArray;

	void shuffleOneRandom(int* arr) {
		int firstIndex = getKey() - keyRangeLB;
		int secondIndex = getKey() - keyRangeLB;
		int first = arr[firstIndex];
		int second = arr[secondIndex];
		int temp = second;
		arr[secondIndex] = first;
		arr[firstIndex] = temp;
	}

	RandomGenerator(int newKeyRangeLB, int newKeyRangeUB) {
		keyRangeLB = newKeyRangeLB;
		keyRangeUB = newKeyRangeUB;

		int size = keyRangeUB - keyRangeLB;

		// create key array
		keyArray = new int[size];
		for (int i = 0; i < size; ++i)
			keyArray[i] = (size - i);

		for (int i = 0; i < size; ++i)
			shuffleOneRandom(keyArray);
	}

private:

	int getKey() {
		// initialize RNG (using Mersenne Twister)
		generator = mt19937();
		generator.seed(random_device()());
		keyRandom = uniform_int_distribution<mt19937::result_type>(keyRangeLB, keyRangeUB - 1);
		return keyRandom(generator);
	}
};

#endif