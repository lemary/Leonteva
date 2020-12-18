#include <iostream>
#include <vector>

using std::cin;
using std::cout;

int partition(std::vector<int> &mas, int l, int r){
    int id = l;
    id += rand() % (r - l + 1);
    std::swap(mas[r], mas[id]);
    int p = l;
    for(int i = l; i <= r; i++){
        if(i == r){
            std::swap(mas[r], mas[p]);
            return p;
        }
        if(mas[i] < mas[r]){
            std::swap(mas[i],mas[p]);
            p++;
        }
    }
}

int kth(std::vector<int> &mas, int l, int r, int k) {
    if (l == r) {
        return mas[l];
    }
    int pivotId = partition(mas, l, r);
    if(pivotId - l > k){
        return kth(mas, l, pivotId-1, k);
    }else{
        return kth(mas, pivotId, r, k - (pivotId - l));
    }
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
    cout << kth(A, 0, n-1, k);
}
