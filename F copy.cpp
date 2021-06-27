#include <iostream>
using namespace std;

int main() {
    int INF = 1e9;
    int n;
    cin >> n;
    int graph[n][n];

    for (auto l = 0; l < n; l++)
        for (auto k = 0; k < n; k++)
            cin >> graph[l][k];

    std::pair<int, int> dp[n][(1 << n)];

    for (auto l = 0; l < n; l++)
        for (auto k = 0; k < (1 << n); k++) {
            dp[l][k].first = INF;
            dp[l][1 << l].first = 0;
        }

    for (unsigned int m = 1; m < (1 << n); m++)
        for (unsigned int v = 0; v < n; v++)
            if ((m >> v) & 1) {
                for (int u = 0; u < n; u++) {
                    if ((m >> u) & 1) continue;

                    int new_m = (m | (1 << u));
                    dp[u][new_m].first = std::min(dp[v][m].first + graph[u][v], dp[u][new_m].first);

                    if (dp[u][new_m].first == (dp[v][m].first + graph[u][v])) dp[u][new_m].second = v;
                }
            }

    int min = INF;
    int min_node = 0;

    for (auto node = 0; node < n; node++ )  //////
        if (min > dp[node][(1 << n) - 1].first) {
            min = dp[node][(1 << n) - 1].first;
            min_node = node;
        }

    cout << min << '\n';

    int mask;
    mask = (1 << n) - 1;

    cout << min_node + 1 << " ";

    for (auto i = 0; i < n-1; i++) {
        int prev;
        prev = dp[min_node][mask].second;
        cout << prev + 1 << " ";
        mask ^= 1 << min_node; //////
        min_node = prev;
    }
}