#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct DFS {
    std::vector<std::vector<long long>> node_ed;
    std::vector<std::string> node_c;
    std::vector<long long> time_in, time_out;
    long long time;

    DFS(long long);
    void do_DFS(long long);
    bool answer(long long, long long);
};

DFS::DFS(long long n) {
    for (auto k = 0; k < n + 1; k++) {
        node_ed.push_back(std::vector<long long>());
        node_c.push_back("WHITE");
        time_in.push_back(0);
        time_out.push_back(0);
    }
    time = 0;
}

void DFS::do_DFS(long long numb) {
    time_in[numb] = time++;
    node_c[numb] = "GREY";
    for (auto k = 0; k < node_ed[numb].size(); k++) ///////////////
        if (node_c[node_ed[numb][k]] != "WHITE") continue;
        else do_DFS(node_ed[numb][k]);
    node_c[numb] = "BLACK";
    time_out[numb] = time++;
}

bool DFS::answer(long long n_1, long long n_2) {
    return (time_in[n_1] < time_in[n_2] && time_out[n_1] > time_out[n_2]);
}

int main() {
    long long n, root, prev, num, x, y, ans;
    cin >> n;
    DFS graph(n);
    for (auto k = 1; k < n + 1; k++) {
        cin >> prev;
        if (prev == 0) root = k;
        else graph.node_ed[prev].push_back(k);
    }
    graph.do_DFS(root);
    cin >> num;
    for (auto k = 0; k < num; k++) {
        cin >> x >> y;
        ans = graph.answer(x, y);
        cout << ans << '\n';
    }
}