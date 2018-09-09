#ifndef KVPAIR
#define KVPAIR

class KVPair {
public:
	int key;
	int value;

	KVPair() {
		key = -1; // "empty" slot flag
		value = -1;
	}

	KVPair(int newKey, int newValue) {
		key = newKey;
		value = newValue;
	}
};

#endif