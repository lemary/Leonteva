#include <iostream>
#include <vector>

using std::cin;
using std::cout;

int partition(std::vector<int> &mas, int l, int r){
    int id = rand() % (r - l + 1) + l;
    std::vector<int> buf(r-l+1);
    int fs = 0;
    int ls = r-l;
    for(int i = l; i <= r; ++i){
        if(i != id){
            if(mas[i] < mas[id]){
                buf[fs] = mas[i];
                fs++;
            }else{
                buf[ls] = mas[i];
                ls--;
            }
        }
    }
    buf[fs] = mas[id];
    for(int i = l; i <= r; ++i){
        mas[i] = buf[i-l];
    }
    return l+fs;
}

int kth(std::vector<int> &mas, int k) {
    int l = 0, r = mas.size()-1;
    while (l != r) {
        int pivotId = partition(mas, l, r);
        if(pivotId - l > k){
            r = pivotId - 1;
        }else{
            l = pivotId;
            k -= pivotId - 1;
        }
    }
    return mas[l];
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    std::vector<int> A(n);
    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }
    cout << kth(A, k);
}
