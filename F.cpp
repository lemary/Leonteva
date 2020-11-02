#include <iostream>
#include <vector>
 
using namespace std;

long long merge(vector<int>& B, vector<int>& C, vector<int> &mas) { //тупа слияние!!!
    int i = 0, j = 0;
    long long ANS = 0;
    int c = 0;
    while (i < B.size() && j < C.size()) {
        if (B[i] < C[j]) {
            mas.push_back(B[i]);
            ANS += c;
            ++i;
        } else {
            mas.push_back(C[j]);
            ++c;
            ++j;
        }
    }
    while (i < B.size()) {
        mas.push_back(B[i]);
        ANS += c;
        ++i;
    }
    while (j < C.size()) {
        mas.push_back(C[j]);
        ++c;
        ++j;
    }
    return ANS;
}

long long msort(vector<int>& mas) { //MergeSort
    int n = mas.size();
    if (n == 1) {
        return 0;
    }
    long long ans = 0;
    std::vector<int> B;
    std::vector<int> C;
    for (int i = 0; i < n / 2; ++i) {
        B.push_back(mas[i]);
    }
    for (int i = n / 2; i < n; ++i) {
        C.push_back(mas[i]);
    }
    ans += msort(B);
    ans += msort(C);    
    mas.clear();
    ans += merge(B, C, mas);
    return ans;
}

int main() {
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n = 0;
    cin >> n;
    std::vector<int> mas(n);
    for (int i = 0; i < n; ++i) {
        cin >> mas[i];
    }
    cout << msort(mas) << endl;
}