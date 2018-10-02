#include <iostream>
#include "ProbingHashTable.h"

#include <chrono>                                                  // for delay
#include <thread>                                                  // for delay

using namespace std;

using namespace std::this_thread;                                  // for delay
using namespace std::chrono_literals;                              // for delay
using std::chrono::system_clock;                                   // for delay

const int DEFAULT_PROBING_METHOD = 2;                              // 1. linear 2. quadratic 3. double hashing
const int DEFAULT_INITIAL_CAPACITY = 23;                           // default constructor size

ostream& operator<<(ostream& out, const ProbingHashTable& printHT) {
    int* HT = printHT.getHT();
    int capacity = printHT.getCapacity();

    for (int i = 0; i < capacity; ++i)
        if (HT[i] >= 0)
            cout << "   " << i << ". (" << HT[i] << ")" << endl;
        else
            cout << "   " << i << "." << endl;

    return out;
}

ProbingHashTable::ProbingHashTable() {
    probingMethod = DEFAULT_PROBING_METHOD;
    size = DEFAULT_INITIAL_CAPACITY;
    numItems = 0;
    HT = new int[size];

    for (int i = 0; i < size; ++i)
        HT[i] = -1;
}

ProbingHashTable::ProbingHashTable(int newProbingMethod) {
    probingMethod = newProbingMethod;
    size = DEFAULT_INITIAL_CAPACITY;
    numItems = 0;
    HT = new int[size];

    for (int i = 0; i < size; ++i)
        HT[i] = -1;
}

void ProbingHashTable::insertKey(int key) {                        // function insertKey
    bool foundOpen = false;
    bool cycled = false;
    int j = 0;
    int hashedKey;

    while (!foundOpen && !cycled) {                                //  - while no open spots and no cycle
        hashedKey = hash(key, j);                                  //    - compute hash

        if (j > size)                                              //    - check if cycled depending on probing method
            cycled = true;
        else if (probingMethod == 2 && j >= (size + 1) / 2)
            cycled = true;
        else if (hashedKey < 0)
            cycled = true;

        if (HT[hashedKey] < 0)                                     //    - if empty or deleted
            foundOpen = true;                                      //      - insert
        else                                                       //    - else
            ++j;                                                   //      - increment j
    }

    if (foundOpen) {                                               //  - if found open spot
        HT[hashedKey] = key;                                       //    - insert
        ++numItems;
    } else {                                                       //  - else
        rehash();                                                  //    - rehash
        insertKey(key);                                            //    - insert
    }
}

bool ProbingHashTable::searchKey(int key) const {                  // function searchKey
    if (searchKeyIndex(key) >= 0) return true;
    else return false;
}

int ProbingHashTable::stepsBefore(int key) const {                 // function stepsTo
    bool found = false;
    bool done = false;
    int j = 0;
    int steps = 0;

    while (!found && !done) {                                      // - while not found and not cycled
        int hashedKey = hash(key, j);

        if (HT[hashedKey] == key) {                                //   - if found our key
            found = true;                                          //     - found = true
            done = true;
        }
        else if (HT[hashedKey] == -1)                              //   - if hit empty index
            done = true;
        else if (probingMethod == 2 && j == (size / 2) + 1)        //   - if cycled (quadratic)
            done = true;
        else if (j > size)                                         //   - if cycled (linear / double hashing)
            done = true;
        else                                                       //   - if hit colliding or deleted element
            ++j;

        ++steps;
    }

    return steps;
}

bool ProbingHashTable::deleteKey(int key) {                        // function deleteKey
    bool deleted = false;

    int place = searchKeyIndex(key);                               // - call private search function (returns index)

    if (place != -1) {                                             // - if found
        deleted = true;
        HT[place] = -2;                                            //   - set key to -2 (deleted flag)
    }

    return deleted;
}

void ProbingHashTable::rehash() {                                  // function rehash
    int oldSize = size;
    int *oldHT = HT;

    size = nextPrime(size * 2);                                    //  - compute new size (2 * cap) -> next prime
    HT = new int[size];

    for (int i = 0; i < size; ++i) 
        HT[i] = -1;

    for (int i = 0; i < oldSize; ++i)                              // - traverse linearly
        if (oldHT[i] >= 0)                                         //   - if not empty / deleted element
            insertKey(oldHT[i]);                                   //     - insert

    delete[] oldHT;
}


void ProbingHashTable::resetTable() {
    delete[] HT;
    HT = nullptr;
    numItems = 0;
    size = 0;
}

ProbingHashTable& ProbingHashTable::operator=(const ProbingHashTable& copyHT) {
    if (this != &copyHT) {
        delete[] HT;
        numItems = copyHT.numItems;
        size = copyHT.size;
        HT = new int[size];

        for (int i = 0; i < size; ++i)
            HT[i] = copyHT.HT[i];
    }
    else
        cerr << "Attempted assignment to itself." << endl;

    return *this;
}

int ProbingHashTable::searchKeyIndex(int key) const {
    bool cycled = false;
    int j = 0;

    while (!cycled) {
        int hashedKey = hash(key, j);

        if (j >= size)
            cycled = true;
        else if (probingMethod == 2 && j >= (size + 1) / 2)        // quadratic
            cycled = true;
        
        if (HT[hashedKey] < 0)
            return hashedKey;
        else
            ++j;
    }

    return -1;
}

int ProbingHashTable::nextPrime(int i) const {
    bool found = false;
    while (!found) {
        ++i;
        bool prime = true;
        for (int j = 2; j * j <= i; ++j)
            if (i % j == 0)
                prime = false;

        if (prime)
            found = true;
        else ++i;
    }

    return i;
}

int ProbingHashTable::prevPrime(int i) const {
    bool found = false;
    while (!found) {
        --i;
        bool prime = true;
        for (int j = 2; j * j < i; ++j)
            if (i % j == 0)
                prime = false;

        if (prime) found = true;
    }

    return i;
}

void ProbingHashTable::timedSearch(int *keyArray, int numKeys) const {
    int steps = 0;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    for (int i = 0; i < numKeys; ++i)
        steps += stepsBefore(keyArray[i]);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Searched for " << numKeys << " keys in "
        << chrono::duration_cast<chrono::microseconds>(end - begin).count()
        << " microseconds" << endl;

    double avgSteps = static_cast<double>(steps) / static_cast<double>(numKeys);
    cout << "Searching time complexity: O(" << avgSteps << ")" << endl;
    double avgTime = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - begin).count()) / numKeys;
    cout << "Avg. time to find a key: " << avgTime << " microseconds" << endl << endl;
}