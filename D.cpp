#include <iostream>
#include <deque>
#include <queue>

using std::cin;
using std::cout;

int main() {
    std::deque<int> p;
    std::queue<int> l;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        char c;
        int k;
        cin >> c;
        if (c == '+') { // Добавить в конец
            cin >> k;
            p.push_back(k);
            if (l.size() < p.size()) {
                l.push(p.front()); 
                p.pop_front();  
            }
        } else if (c == '-') { // Взять с начала
            cout << l.front() << "\n"; 
            if (l.size() == p.size()) {
                l.pop();
                l.push(p.front());
                p.pop_front();
            } else {   
                l.pop();
            }
        } else if (c == '*') { // Добавить в середину
            cin >> k;
            if (l.size() == p.size()) {
                l.push(k);
            } else {
                p.push_front(k);
            }
        }
    }
}