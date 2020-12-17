#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using std::cin;
using std::cout;

void add(std::vector<std::set<long long>>& MN, std::map<long long, std::set<int>>& EL, int s, long long e) {
    if (EL.find(e) == EL.end()) {
        EL[e] = std::set<int>();
    }
    EL[e].insert(s);
    MN[s].insert(e);
}

void del(std::vector<std::set<long long>>& MN, std::map<long long, std::set<int>>& EL, int s, long long e) {
    EL[e].erase(s);
    MN[s].erase(e);
}

void clearing(std::vector<std::set<long long>>& MN, std::map<long long, std::set<int>>& EL, int s) {
    for (long long i : MN[s]) {
        EL[i].erase(s);
    }
    MN[s].clear();
}

void listset(std::vector<std::set<long long>>& MN, std::map<long long, std::set<int>>& EL, int s) {
    if (MN[s].empty()) {
        cout << -1 << '\n';
    } else {
        for (long long i : MN[s]) {
            cout << i << " ";
        }
        cout << '\n';
    }
}

void listsetsof(std::vector<std::set<long long>>& MN, std::map<long long, std::set<int>>& EL, long long e) {
    if (EL[e].empty()) {
        cout << -1 << '\n';
    } else {
        for (int i : EL[e]) { 
            cout << i << " ";
        }
        cout << '\n';
    }
}

////////////////////////////

main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int m, k, s;
    long long e, n;
    std::string x;
    std::vector<std::set<long long>> MN(100001, std::set<long long>());
    std::map<long long, std::set<int>> EL;
    cin >> n >> m;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> x;
        if (x == "ADD") {
            cin >> e >> s;
            add(MN, EL, s, e);
        }
        if (x == "DELETE") {
            cin >> e >> s;
            del(MN, EL, s, e);
        }
        if (x == "CLEAR") {
            cin >> s;
            clearing(MN, EL, s);
        }
        if (x == "LISTSET") {
            cin >> s;
            listset(MN, EL, s);
        }
        if (x == "LISTSETSOF") {
            cin >> e;
            listsetsof(MN, EL, e);
        }
    }
}