#include <iostream>

using std::cin;
using std::cout;
 
int getByte(long long number, int n) {
    return (number >> (8 * n)) & 255;
}
 
void countingSort(long long *data, int size, int n) {
    int counters[256] = {};// Создавать каждый раз массив не самая лучшая идея, но в данном случае не критично, учитывая сколько стоит его очистить

    for(int i = 0; i < size; i++) {
        counters[getByte(data[i], n)]++;
    }
 
    for(int i = 1; i < 256; i++) {
        counters[i] += counters[i - 1];
    }
 
    long long *tmp = new long long[size];
 
    for(int i = size - 1; ; i--) {
        tmp[--counters[getByte(data[i], n)]] = data[i];
        if(i == 0)
            break;
    }
 
    for(int i = 0; i < size; i++) {
        data[i] = tmp[i];
    }
}
 
void LSDSort(long long *data, int size) {
    int totalBytes = 8;
 
    for(int byte = 0; byte < totalBytes; byte++) {
        countingSort(data, size, byte);
    }
}
 
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n = 0;
    cin >> n;
 
    long long* data = new long long[n];
    for(int i = 0; i < n; i++) {
        cin >> data[i];
    }
 
    LSDSort(data, n);
    
    for(int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
}
