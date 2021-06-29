#include <iostream>
using namespace std;

struct Matrix {
    unsigned long long array[5][5];
    Matrix();
    Matrix(int);
    Matrix& operator=(const Matrix&);
    friend Matrix operator*(const Matrix&, const Matrix&);
    friend Matrix operator%(const Matrix&, const long long&);
};

Matrix::Matrix() {
    for (auto l = 0; l < 5; l++)
        for (auto k = 0; k < 5; k++)
            array[l][k] = 1;
    array[3][2] = 0;
    array[3][4] = 0;
    array[4][2] = 0;
    array[4][4] = 0;
}

Matrix::Matrix(int) {
    for (auto l = 0; l < 5; l++)
        for(auto k = 0; k < 5; k++) {
            array[l][k] = 0;
            if (k == l) array[l][k] = 1;
        }
}

Matrix& Matrix::operator=(const Matrix& value) {
    for (auto l = 0; l < 5; l++)
        for(auto k = 0; k < 5; k++)
            array[l][k] = value.array[l][k] % 999999937;
    return *this;
}

Matrix operator*(const Matrix& left, const Matrix& right) {
    Matrix ans;
    unsigned long long s;
    for (auto l = 0; l < 5; l++)
        for(auto k = 0; k < 5; k++) {
            s = 0;
            for (auto m = 0; m < 5; m++)
                s = (s + (left.array[l][m] * right.array[m][k]) % 999999937) % 999999937;
            ans.array[l][k] = s % 999999937;
        }
    return ans;
}

Matrix operator%(const Matrix& left, const unsigned long long& right) {
    Matrix cop;
    cop = left;
    for (auto l = 0; l < 5; l++)
        for(auto k = 0; k < 5; k++)
            cop.array[l][k] %= 999999937;
    return cop;
}

Matrix toDeg(Matrix val, unsigned long long d) {   
    unsigned long long md;
    md = 999999937;
    Matrix ans(1);
    Matrix p = val;
    while (d) {
        if (d & 1) {
            p = p % md;
            ans = ((ans % md) * p) % md;
        }
        p = (p*p) % md % md;
        d = d >> 1;
    }
    return ans;
}

int main() {
    unsigned long long n, s;
    cin >> n ;
    while (n != 0) {
        Matrix G;
        G = toDeg(G, n - 1);
        s = 0;
        for (auto l = 0; l < 5; l++)
            for (auto k = 0; k < 5; k++) {
                s += G.array[l][k];
                s %= 999999937;
            }
        cout << s << '\n';
        cin >> n;
    }
    
}
