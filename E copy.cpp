#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class HashTable {
public:
    void toChange(std::pair<std::string, std::string>&);
    void get(std::string);
    void remove(std::string);
private:
    std::list<std::pair<std::string, std::string>> array[100000];
    unsigned long long getHash(const std::string&);
};

unsigned long long HashTable::getHash(const std::string& key) {
    long long answer = 1000000000;
    unsigned int hash = 0;
    for (int j = 0; j < key.size(); j++) {
        hash = hash + (unsigned char)(key[j]);
        hash = hash + (hash << 10);
        hash = hash ^ (hash >> 6);
    }
    hash = hash + (hash << 3);
    hash = hash ^ (hash >> 11);
    hash = hash + (hash << 15);
    answer = answer % 100000;
    answer = hash / 1000000 - answer;
    return answer;
}

void HashTable::toChange(std::pair<std::string, std::string> &value) {
    unsigned long long hash = getHash(value.first);
    bool indicator_change = false;
    for (auto i = array[hash].begin(); i != array[hash].end(); ++i) {
        if ((*i).first == value.first) {
            (*i).second = value.second;
            indicator_change = true;
        }
        if (indicator_change) {
            break;
        }
    }
    if (!indicator_change) array[hash].push_back(value);
}

void HashTable::get(std::string key) {
    unsigned long long hash = getHash(key);
    bool Indicator_in = false;
    for (auto i = array[hash].begin(); i != array[hash].end(); ++i) {
        if ((*i).first == key) {
            cout << (*i).second << '\n';
            Indicator_in = true;
        }
        if (Indicator_in) {
            break;
        }
    }
    if (!Indicator_in) {
        cout << "none" << '\n';
    }
}

void HashTable::remove(std::string key) {
    unsigned long long hash = getHash(key);
    bool Indicator_in = false;
    for (auto i = array[hash].begin(); i != array[hash].end(); ++i) {
        if ((*i).first == key) {
            array[hash].erase(i);
            Indicator_in = true;
        }
        if (Indicator_in) {
            break;
        }
    }
}

int main() {
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    HashTable hashTable;
    std::string key;
    std::string value;
    std::string commanda;
    while (cin >> commanda) {
        if (commanda == "get") {
            cin >> key;
            hashTable.get(key);
        }
        if ( commanda == "put" ) {
            cin >> key >> value;
            std::pair<std::string, std::string> val;
            val = std::make_pair(key, value);
            hashTable.toChange(val);
        }
        if (commanda == "delete") {
            cin >> key;
            hashTable.remove(key);
        }
    }
}