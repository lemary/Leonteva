#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <set>
using namespace std;

struct DFS {
    std::set<long long> node_s;
    std::vector<std::string> node_c;
    std::vector<std::vector<long long>> node_ed;
    std::vector<long long> tin, ret;
    long long ans_ed, time;

    DFS(long long);
    void DoDFS(long long, long long);
};

DFS::DFS(long long n) {
    for (auto k = 0; k < n; k++) {
        node_ed.push_back(std::vector<long long>());
        node_c.push_back("WHITE");
        tin.push_back(0);
        ret.push_back(0);
    }
    time = 0;
    ans_ed = 0;
}

void DFS::DoDFS(long long node, long long par) {
    int ch = 0;
    tin[node] = time++;
    ret[node] = time++;
    node_c[node] = "GREY";
    for (auto k = 0; k < node_ed[node].size(); k++) {
        if (node_ed[node][k] == par) continue;
        if (node_c[node_ed[node][k]] == "GREY") ret[node] = std::min(ret[node], tin[node_ed[node][k]]);
        else {
            DoDFS(node_ed[node][k], node);
            ch = ch + 1;
            if (par != -1) {
                if (tin[node] <= ret[node_ed[node][k]]) node_s.insert(node);
            } ////////////////
            else if (ch >= 2) node_s.insert(node);
            ret[node] = std::min(ret[node_ed[node][k]], ret[node]);
        }
    }
}

int main() {
    long long v, m, x, y;
    cin >> v;
    cin >> m;
    DFS graph(v);
    for (auto k = 0; k < m; k++) {
        cin >> x >> y;
        x = x - 1;
        y = y - 1;
        graph.node_ed[x].push_back(y);
        graph.node_ed[y].push_back(x);
    }
    graph.DoDFS(x, -1);
    cout << graph.node_s.size() << endl;
    for (auto k = graph.node_s.begin(); k != graph.node_s.end(); k++)
        cout << *k  + 1 << ' ';
}
