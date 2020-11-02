#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;


struct Node{
    long long val;
    int index;
};

struct Heap{
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
    while(v > 1 && heap->nodes[v]->val < heap->nodes[v/2]->val) {
        swapNodes(heap, v, v/2);
        v /= 2;
    }
}

void siftDown(Heap* heap, int v){
    while (2*v <= heap->size) {
        int j = -1;
        if(heap->nodes[2*v]->val < heap->nodes[v]->val) j = 2*v;
        if(2*v + 1 <= heap->size && heap->nodes[2*v + 1]->val < heap->nodes[v]->val && (j == -1 || heap->nodes[2*v]->val > heap->nodes[2*v + 1]->val)) j = 2*v + 1;
        if(j == -1) break;
        swapNodes(heap, v, j);
        v = j;
    }
}

long long getMin(Heap* heap){
    return heap->nodes[1]->val;
}

void eraseMin(Heap* heap){
    swapNodes(heap, 1, heap->size);
    delete heap->nodes[heap->size];
    //heap->nodes[heap->size] = nullptr;
    heap->size--;
    if(heap->size > 0){
        siftDown(heap, 1);
    }
}

Node* insert(Heap* heap, int value){
    heap->size++;
    Node* node = new Node();
    node->index = heap->size;
    node->val = value;
    heap->nodes[heap->size] = node;
    //cout << "added" << value << std::endl;
    siftUp(heap, heap->size);
    //cout << "sifted Up" << std::endl;
    return node;
}

void outHeap(Heap* heap){
    cout << "heap: ";
    for(int i = 0; i < heap->nodes.size(); i++){
        if(heap->nodes[i]==nullptr) cout << "! ";
        else cout << heap->nodes[i]->val << " ";
    }
    cout << std::endl;
}

void decreaseKey(Heap* heap, int v, int dt){
    heap->nodes[v]->val -= dt;
    siftUp(heap,v);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> q;
    std::string s;
    std::vector<Node*> nodes(q, nullptr);
    Heap heap = Heap();
    init(&heap, 100000);
    for(int i = 0; i < q; ++i){
        cin>>s;
        if(s=="insert"){
            int x;
            cin >> x;
            //cout << "inserting " << x << std::endl;
            nodes[i] = insert(&heap, x);
        }else{
            nodes[i] = nullptr;
        }
        if(s=="getMin") cout << getMin(&heap) << "\n";
        if(s=="extractMin") eraseMin(&heap);
        if(s=="decreaseKey") {
            int delta, ind;
            cin >> ind >> delta;
            ind--;
            decreaseKey(&heap, nodes[ind]->index, delta);
        }
    }
}