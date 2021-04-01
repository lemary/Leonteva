#include <iostream>

using std::cin;
using std::cout;

int main() {
    int beck = 1e9, n;
    cin >> n;

    int graph[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    std::pair <int, int> dp[n][(1 << n)];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            dp[i][j].first = beck;
            dp[i][1 << i].first = 0;
        }
    }

    for (unsigned int mask = 1; mask < (1 << n); ++mask) {
        for (unsigned int node_v = 0; node_v < n; ++node_v) {
            if ((mask >> node_v) & 1) {
                for (int node_u = 0; node_u < n; ++node_u) {
                    if ((mask >> node_u) & 1) continue;
                    int new_mask = (mask | (1 << node_u));
                    dp[node_u][new_mask].first = std::min(dp[node_u][new_mask].first, dp[node_v][mask].first + graph[node_u][node_v]);
                    if (dp[node_u][new_mask].first == (dp[node_v][mask].first + graph[node_u][node_v])) {
                        dp[node_u][new_mask].second = node_v;
                    }
                }
            }
        }
    }

    int min = beck;
    int min_node = 0;
    //std::cout << dp[1][1 << 1];

    for (int node = 0; node < n; ++node ) {
        if (min > dp[node][(1 << n) - 1].first) {
            min = dp[node][(1 << n) - 1].first;
            min_node = node;
        }
    }

    cout << min << '\n';
    int mask = (1 << n) - 1;
    cout << min_node + 1 << " ";
    
    for (int i = 0; i < n-1; ++i) {
        int prev = dp[min_node][mask].second;
        cout << prev + 1 << " ";
        mask = mask ^ (1 << min_node);
        min_node = prev;
    }
    
    return 0;
}
