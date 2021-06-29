#include <iostream>

using namespace std;

int main() {
    long long number;
    long long bag;
    cin >> bag >> number;
    long long elements[number + 1];
    elements[0] = 0;

    for (auto k = 1; k - 1 < number; k++)
        cin >> elements[k];

    long long dp[number + 1][bag + 1];// Для простого рюкзака можно было и одномерным массивом воспользоваться
    for (auto j = 0; j - 1 < number; j++)
        for (auto k = 0; k - 1 < bag; k++)
            dp[j][k] = 0;

    for (auto j = 1; j - 1 < number; j++)
        for (auto k = 0; k - 1 < bag; k++) {
            dp[j][k] = std::max(dp[j][k], dp[j - 1][k]);
            if (elements[j] + k < bag + 1) dp[j][k + elements[j]] = std::max(dp[j][k + elements[j]], dp[j - 1][k] + elements[j]);
        }

    long long minimum = 0;
    for (auto j = 1; j - 1 < number; j++)
        for (auto k = 1; k - 1 < bag; k++)
            if (minimum < dp[j][k]) minimum = dp[j][k];
    cout << minimum;
}
