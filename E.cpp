#include <iostream>
#include <vector>
 
using std::cin;
using std::cout;
 
// Решение на 2 балла - в онлайне
 
class Segment {
public:
    Segment(int left, int right) {
        segL = left;
        segR = right;
        segM = (left + right) / 2;
        sum = 0;
        l = nullptr;
        r = nullptr;
    }
 
    ~Segment(){
        delete l;
        delete r;
    }
 
    long long getSum(int leftQ, int rightQ) {
        if (segL == leftQ && segR == rightQ) {
            return sum;
        }
        if (rightQ <= segM) {
            if(l == nullptr) {
                l = new Segment(segL, segM);
            }
            return l->getSum(leftQ, rightQ);
        } else if(leftQ > segM) {
            if(r == nullptr) {
                r = new Segment(segM + 1, segR);
            }
            return r->getSum(leftQ, rightQ);
        } else {
            if(l == nullptr) {
                l = new Segment(segL, segM);
            }
            if(r == nullptr) {
                r = new Segment(segM + 1, segR);
            }
            return l->getSum(leftQ, segM) + r->getSum(segM + 1, rightQ);
        }
    }
 
    void addValue(int index, int value) {
        if(segL == index && segR == index){
            sum += value;
            return;
        }
        if(l == nullptr) {
            l = new Segment(segL, segM);
        }
        if(r == nullptr) {
            r = new Segment(segM + 1, segR);
        }
        if (index <= segM) {
            l->addValue(index, value);
        } else {
            r->addValue(index, value);
        }
        sum = l->sum +  r->sum;
        return;
    }
private:
    Segment* l;
    Segment* r;
    int segL;
    int segR;
    int segM;
    long long sum;
};
 
int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int q, x;
    char t;
    cin >> q;
    Segment tree = Segment(0, 1e9);
    for (int i = 0; i < q; i++) {
        cin >> t >> x;
        if (t == '+') {
            tree.addValue(x, x);
        } else {
            cout << tree.getSum(0, x) << "\n";
        }
    }
    return 0;
}