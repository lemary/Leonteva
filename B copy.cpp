#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <cmath>

using namespace std;

class HashTable {
public:
    void swap(long long, long long);
private:
    std::list<std::pair<long long, long long>> array[100000];
    unsigned long long getHash(const int&);
};

unsigned long long HashTable::getHash(const int& key) {
    unsigned long long hash = 0;
    long long i = 1;
    long long x = 983;
    long long mod = std::numeric_limits<long long int>::max();
    long long copy_key = key;

    while (copy_key != 0) {
        hash = hash + (long long)pow(x,i) * ( copy_key % 10 );
        i += 1;
        hash = hash % mod;
        copy_key = copy_key / 10;
    }
    
    hash = (hash % mod) % 100000;
    return hash;
}

void HashTable::swap(long long key_1, long long key_2) {
    long long hash_1 = getHash(key_1);
    long long hash_2 = getHash(key_2);
    bool Indicator_hash1_in = false;
    bool Indicator_hash2_in = false;
    auto element_key1 = array[hash_1].begin();
    auto element_key2 = array[hash_2].begin();

    for (auto k = array[hash_1].begin(); k != array[hash_1].end() ; ++k) {
        if ( (*k).first == key_1 ) {
            Indicator_hash1_in = true;
            element_key1 = k;
        }
        if (Indicator_hash1_in) {
            break;
        }
    }
    if (!Indicator_hash1_in) {
        std::pair<long long, long long> value = std::make_pair(key_1, key_1);
        array[hash_1].push_back(value);
        element_key1 = array[hash_1].end();
        --element_key1;
    }
    for (auto k = array[hash_2].begin(); k != array[hash_2].end(); ++k) {
        if ((*k).first == key_2) {
            Indicator_hash2_in = true;
            element_key2 = k;
        }
        if (Indicator_hash2_in) {
            break;
        }
    }
    if (!Indicator_hash2_in) {
        std::pair<long long, long long> value = std::make_pair(key_2, key_2);
        array[hash_2].push_back(value);
        element_key2 = array[hash_2].end();
        --element_key2;
    }

    std::swap((*element_key1).second,(*element_key2).second);
    cout << std::abs((*element_key1).second - (*element_key2).second) << '\n';
}

int main() {
    HashTable hashTable;
    long long numeral;
    cin >> numeral;
    long long key1;
    long long key2;
    for (int i = 0; i < numeral; ++i) {
        cin >> key1 >> key2;
        hashTable.swap(key1, key2);
    }
}