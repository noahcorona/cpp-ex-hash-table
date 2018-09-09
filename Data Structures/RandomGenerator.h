#ifndef RANDOMGENERATOR
#define RANDOMGENERATOR

#include <random>

using namespace std;

class RandomGenerator {
public:
	RandomGenerator(int newKeyRangeLB, int newKeyRangeUB, int newValueRangeLB, int newValueRangeUB) {
		keyRangeLB = newKeyRangeLB;
		keyRangeUB = newKeyRangeUB;
		valueRangeLB = newValueRangeLB;
		valueRangeUB = newValueRangeUB;
	}

	int getKey() {
		// initialize RNG (using Mersenne Twister)
		generator = mt19937();
		generator.seed(random_device()());
		keyRandom = uniform_int_distribution<mt19937::result_type>(keyRangeLB, keyRangeUB);
		valueRandom = uniform_int_distribution<mt19937::result_type>(valueRangeLB, valueRangeUB);
		return keyRandom(generator);
	}

	int getValue() {
		// initialize RNG (using Mersenne Twister)
		generator = mt19937();
		generator.seed(random_device()());
		keyRandom = uniform_int_distribution<mt19937::result_type>(keyRangeLB, keyRangeUB);
		valueRandom = uniform_int_distribution<mt19937::result_type>(valueRangeLB, valueRangeUB);
		return valueRandom(generator);
	}

private:
	mt19937 generator;
	uniform_int_distribution<mt19937::result_type> keyRandom;
	uniform_int_distribution<mt19937::result_type> valueRandom;
	int keyRangeLB;
	int keyRangeUB;
	int valueRangeLB;
	int valueRangeUB;
};

#endif