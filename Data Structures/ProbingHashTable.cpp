#include <iostream>
#include "ProbingHashTable.h"

ProbingHashTable::ProbingHashTable(int newProbingMethod, int newCapacity) {
	probingMethod = newProbingMethod;
	capacity = newCapacity;
	numOfElements = 0;
}

ProbingHashTable::ProbingHashTable(int newProbingMethod, int numKeys, int keyRangeLB, int keyRangeUB, int valueRangeLB, int valueRangeUB) {
	
}