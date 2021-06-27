#include <iostream>
using namespace std;

bool Bit(long long musk, int p) {
    if (((musk & (1 << p)) >> p) == 1) return true;
    else return false;
}

bool IsSquareCorrect(long long musk_f, long long musk_s, int p) {
    return !(Bit(musk_f, p) == Bit(musk_f, p + 1) &&
            Bit(musk_f, p) == Bit(musk_s, p) &&
            Bit(musk_s, p) == Bit(musk_s, p + 1));
}

bool correct(long long musk_f, long long musk_s, int m) {
    for (auto k = 0; k < m - 1; k++)
        if (!IsSquareCorrect(musk_f, musk_s, k)) return false;
    return true;
}


int main() {
    int n, m;
    cin >> m >> n;
    if (n > m) {
        int c;
        c = n;
        n = m;
        m = c;
    }

    long long maska;
    maska = ( 1 << n);
    long long dp[maska][m];

    for (auto l = 0; l < maska; l++)
        for (auto k  = 0; k < m; k++) {
            dp[l][k] = 0;
            if (k == 0) dp[l][k] = 1;
        }

    for (auto k = 0; k < m - 1; k++)
        for (auto musk_o = 0; musk_o < maska; musk_o++)
            for (auto musk_n = 0; musk_n < maska; musk_n++)
                if (correct(musk_o, musk_n, n)) dp[musk_n][k + 1] = dp[musk_n][k + 1] + dp[musk_o][k];

    int ans = 0;
    for (auto l = 0; l < maska; l++)
        ans = ans + dp[l][m - 1];
    cout << ans;
}
