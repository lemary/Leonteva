#include <iostream>
#include <iterator>
#include <list>

class HashTable {
public:
    HashTable() {
        std::pair<std::string, long long>
        key_value = std::make_pair("bf",3);
        array[3392].push_back(key_value);
    }
    void toChange(std::pair<std::string, long long>&);
private:
    std::list<std::pair<std::string, long long>> array[100000];
    unsigned long long getHash(const std::string&);
};

unsigned long long HashTable::getHash(const std::string& key) {
    long long answer = 1000000000;
    unsigned int hash = 0;

    for (int i=0; i < key.size(); ++i) {
        hash = hash + (unsigned char)(key[i]);
        hash = hash + (hash << 10);
        hash = hash ^ (hash >> 6);
    }

    hash = hash + (hash << 3);
    hash = hash ^ (hash >> 11);
    hash = hash + (hash << 15);
    answer = answer % 100000;
    answer = (hash / 1000000) - answer;

    return answer;
}

void HashTable::toChange(std::pair<std::string, long long> &value) {
    unsigned long long hash = getHash(value.first);
    bool Indicator_change = false;
    for (auto element = array[hash].begin(); element != array[hash].end(); ++element) {
        if ((*element).first == value.first) {
            (*element).second += value.second;
            Indicator_change = true;
            std::cout << (*element).second << " ";
        }
        if (Indicator_change) {
            break;
        }
    }
    if (!Indicator_change) {
        array[hash].push_back(value);
        std::cout << value.second << " ";
    }
}

int main() {
    HashTable HTable;
    std::string key;
    while (std::cin >> key) {
        long long value;
        std::cin >> value;
        std::pair <std::string,long long>  key_value = std::make_pair(key,value);
        HTable.toChange(key_value);
    }
    return 0;
}