#include <iostream>
//#include <vector>
using std::cin;
using std::cout;

int main() { // вся функциональность в main
    
    int size, size2;

    cin >> size;
    int mas[size + 1]; // Массивы неконстантного размера, а также большого константного размера необходимо выделять в динамической памяти.
    for (int i = 1; i < size + 1; ++i) {
        cin >> mas[i];
    }

    cin >> size2;
    int mas2[size2 + 1];
    for (int i = 1; i < size2 + 1; ++i) {
        cin >> mas2[i];
    }

    int ans[size + 1][size2 + 1];

    // for (std::vector<int>& v : mas) { нежизнеспособно
    //     for (int i : v) {
    //         i = 0;
    //     }
    // }

    for (int i = 0; i < size + 1; ++i) {
        for (int k = 0; k < size2 + 1; ++k) {
            ans[i][k] = 0;
        }
    }

    for (int i = 1; i < size + 1; ++i) {
        for (int k = 1; k < size2 + 1; ++k) {
            if (mas[i] != mas2[k]) {
                ans[i][k] = std::max(ans[i][k - 1], ans[i - 1][k]);
            } else {
                ans[i][k] = ans[i - 1][k - 1] + 1;
            }
        }
    }

    cout << ans[size][size2] << '\n';
    return 0;
}
