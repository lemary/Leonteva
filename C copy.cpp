#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

struct DFS {
    std::vector<std::string> node_c;
    std::vector<std::vector<long long>> node_ed;
    std::vector<long long> ans;
    long long start_loop_vertex = 0;

    DFS(long long);
    void DoDFS(long long numb);
};

DFS::DFS(long long n) {
    for (auto k = 0; k < n; k++) {
        node_c.push_back("WHITE");
        node_ed.push_back(std::vector<long long>());
    }
}

void DFS::DoDFS(long long numb) {
    node_c[numb] = "GREY";
    ans.push_back(numb);

    for (auto k = 0; k < node_ed[numb].size(); k++) {
        if (node_c[node_ed[numb][k]] == "GREY") {
            start_loop_vertex = node_ed[numb][k];
            throw 1;
        } else if (node_c[node_ed[numb][k]] == "WHITE") DoDFS(node_ed[numb][k]);
    }
    ans.pop_back();
    node_c[numb] = "BLACK";
}

int main() {

    long long v, r, i;
    int x, y;
    cin >> v >> r;
    DFS graph(v);

    for (auto k = 0; k < r; k++) {
        cin >> x >> y;
        x = x - 1;
        y = y - 1;
        graph.node_ed[x].push_back(y);
    }

    try {
        for (auto k = 0; k < graph.node_c.size() ; k++)
            if (graph.node_c[k] == "WHITE") graph.DoDFS(k);
    } catch(...) {}

    if (!graph.ans.empty()) {
        cout << "YES" << endl;
        i = 0;
        for (; i < graph.ans.size(); i++)
            if (graph.ans[i] == graph.start_loop_vertex) break;
        for (; i < graph.ans.size(); ++i)
            cout << (graph.ans[i] + 1) << ' ';
    } else cout << "NO";
}