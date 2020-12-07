#include <iostream>
#include <vector>

using std::cin;
using std::cout;


struct Node{
    int val;
    int index;
};

struct Heap{ //heapOnMax
    std::vector<Node*> nodes;
    int size;
};

void swapNodes(Heap* heap, int v1, int v2){
    std::swap(heap->nodes[v1]->index, heap->nodes[v2]->index);
    std::swap(heap->nodes[v1], heap->nodes[v2]);
}

void init(Heap* heap, int maxSize){
    heap->nodes.resize(maxSize + 1, nullptr);
    heap->size = 0;
}

void siftUp(Heap* heap, int v){
    while(v > 1 && heap->nodes[v]->val > heap->nodes[v/2]->val) {
        swapNodes(heap, v, v/2);
        v /= 2;
    }
}

void siftDown(Heap* heap, int v){
    while (2*v <= heap->size) {
        int j = -1;
        if(heap->nodes[2*v]->val > heap->nodes[v]->val) j = 2*v;
        if(2*v + 1 <= heap->size && heap->nodes[2*v + 1]->val > heap->nodes[v]->val && (j == -1 || heap->nodes[2*v]->val < heap->nodes[2*v + 1]->val)) j = 2*v + 1;
        if(j == -1) break;
        swapNodes(heap, v, j);
        v = j;
    }
}

int getMax(Heap* heap){
    return heap->nodes[1]->val;
}

void eraseMax(Heap* heap){
    swapNodes(heap, 1, heap->size);
    delete heap->nodes[heap->size];
    //heap->nodes[heap->size] = nullptr;
    heap->size--;
    if(heap->size > 0){
        siftDown(heap, 1);
    }
}

void insert(Heap* heap, int value){
    heap->size++;
    Node* node = new Node();
    node->index = heap->size;
    node->val = value;
    heap->nodes[heap->size] = node;
    siftUp(heap, heap->size);
}

void outHeap(Heap* heap){
    cout << "heap: ";
    for(int i = 0; i < heap->nodes.size(); i++){
        if(heap->nodes[i]==nullptr) cout << "! ";
        else cout << heap->nodes[i]->val << " ";
    }
    cout << std::endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    Heap heap = Heap();
    init(&heap, k);
    for(int i = 0; i < n; ++i) {
        int c;
        cin >> c; //getMax, eraseMax, insert
        if(heap.size < k || c < getMax(&heap)){
            if(heap.size == k) eraseMax(&heap);// Можно было просто заранее заполнить кучу, тогда не было бы каждый раз лишней проверки
            insert(&heap, c);
            //cout << "after insertion: ";
        }
        //outHeap(&heap);
    }
    std::vector<int> v;
    v.reserve(k);
    while(heap.size > 0){
        v.push_back(getMax(&heap));
        eraseMax(&heap);
    }
    for(int i = v.size() - 1; i >= 0; --i){
        cout << v[i] << " ";
    }
}
