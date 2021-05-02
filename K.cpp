#include<iostream>
#include<vector>
#include<cmath>

using std::cin;
using std::cout;

int64_t krasava(size_t n, size_t m) { // имена функций должны быть осмысленными
    std::ios::sync_with_stdio(false);
    cin.tie(0);

    std::vector <std::vector<size_t>> mas(n, std::vector<size_t>((1 << m), 0));
    int64_t answer=0;

    for (size_t a = 0; a < 1 << m; a++) {
        mas[0][a] = 1;
    }

    for (size_t a = 1; a < n; a++) {
        for (size_t b = 0; b < 1 << m; b++) {
            for (size_t c = 0; c < 1 << m; c++) {
                if ((((b & c) & ((c & b) >> 1)) == 0) && (((~b & ~c) & ((~c & ~b) >> 1)) % (1<<(m - 1)) == 0)) {  //jyj // очень длинное условие, которое вложно разобрать
                    mas[a][c] = mas[a][c] + mas[a - 1][b];
                }
            }
        }
    }

    for (size_t a = 0; a < pow(2, m); a++) {
        answer = answer + mas[n - 1][a];
    }

    return(answer);
}

int main() {
    size_t n, m;
    cin >> n >> m;

    if (n < m) {
        std::swap(n, m);
    }
    cout << krasava(n, m);
}
