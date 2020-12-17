#include <iostream>
#include <vector>
 
using std::cin;
using std::cout;
 
class Segment {
public:
    Segment(int* a, int n) {
        arr = a;
        t = new int[4 * n];
        buildSegment(1, 0, n - 1);
    }
 
    ~Segment(){
        delete t;
    }
 
    void buildSegment(int v, int segL, int segR) {
        if (segL == segR) {
            t[v] = arr[segR];
            return;
        }
        int segM = (segL + segR) / 2;
        buildSegment(v * 2, segL, segM);
        buildSegment(v * 2 + 1, segM + 1, segR);
        t[v] = t[v * 2];
        if ((segM + 1 - segL) % 2 == 0){
            t[v] += t[v * 2 + 1];
        } else {
            t[v] -= t[v * 2 + 1];
        }
        return;
    }
 
    void changeValue(int v, int segL, int segR, int ind, int val) {
        if(segL == ind && segR == ind) {
            t[v] = val;
            return;
        }
        int segM = (segL + segR) / 2;
        if (ind <= segM) {
            changeValue(v * 2, segL, segM, ind, val);
        } else {
            changeValue(v * 2 + 1, segM + 1, segR, ind, val);
        }
        t[v] = t[v * 2];
        if ((segM + 1 - segL) % 2 == 0){
            t[v] += t[v * 2 + 1];
        } else {
            t[v] -= t[v * 2 + 1];
        }
        return;
    }
 
    int getSum(int v, int segL, int segR, int l, int r) {
        if (segL == l && segR == r) {
            return t[v];
        }
        int tm = (segL + segR) / 2;
        if (r <= tm) {
            return getSum(v * 2, segL, tm, l, r);
        } else if (l > tm) {
            return getSum(v * 2 + 1, tm + 1, segR, l, r);
        } else {
            int leftSum = getSum(v * 2, segL, tm, l, tm);
            int rightSum = getSum(v * 2 + 1, tm + 1, segR, tm + 1, r);
            if ((tm + 1 - l) % 2 == 0){
                leftSum += rightSum;
            } else {
                leftSum -= rightSum;
            }
            return leftSum;
        }
    }
private:
    int* arr;
    int* t;
};
 
int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i){
        cin >> arr[i];
    }
    Segment tree = Segment(arr, n);
    cin >> q;
    for(int i = 0; i < q; i++) {
        int val1, val2, val3;
        cin >> val1 >> val2 >> val3;
        if (val1 == 0) {
            tree.changeValue(1, 0, n - 1, val2 - 1, val3);
        } else {
            cout << tree.getSum(1, 0, n - 1, val2 - 1, val3 - 1) << "\n";
        }
    }
    return 0;
}