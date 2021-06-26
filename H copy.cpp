#include <iostream>

using namespace std;

int main() {
    long long  size_1;
    long long size_2;

    cin >> size_1;
    cin >> size_2;

    long long array_1[size_1];
    long long array_2[size_2];
    long long mini_array[std::min(size_2, size_1) + 1];
    for (long long k = 0; k < std::min(size_2, size_1) + 1; k++) 
        mini_array[k]--;
    for (long long k = 0; k < size_1; k++) 
        cin >> array_1[k];
    for (long long k = 0; k < size_2; k++) 
        cin >> array_2[k];
    long long dp[size_1 + 1][size_2 + 1];
    for (long long i = 0; i < size_1 + 1; i++)
        for (long long j = 0; j < size_2 + 1; j++)
            dp[i][j] = 0;

    for (int i = 1; i - 1 < size_1; i++) {
        long long ind = 0;
        long long top = 0;
        for (long long j = 1; j - 1 < size_2; j++) {
            if (array_1[i - 1] == array_2[j - 1]) {
                for (long long k = ind + 1; k < j; k++) {
                    if (dp[i - 1][k] > dp[i - 1][top] && array_2[k - 1] < array_1[i - 1]) top = k;
                    ind = k;
                }
                dp[i][j] = dp[i - 1][top] + 1;
            }
            else dp[i][j] = dp[i - 1][j];
        }
    }

    int ans = 0;
    for (int j = 0; j < size_2 + 1; j++)
        if (ans < dp[size_1][j]) ans = dp[size_1][j];
    cout << ans;
}