#include <iostream>
#include <string>
#include <time.h>

using std::cin;
using std::cout;

class Node {
public:
    Node(int _value){
        value = _value;
        size = 1;
        prior = (rand() << 15) | rand();
        left = nullptr;
        right = nullptr;
    }
    static Node* add(Node*, int);
    static Node* del(Node*, int);
    static int getMax(Node*&, int);
private:
    int value;
    int prior;
    int size;
    Node* left;
    Node* right;
    static int getSize(Node*);
    static void fixSize(Node*);
    static Node* merge(Node*, Node*);
    static std::pair<Node*, Node*> splitVal(Node*, int);
    static std::pair<Node*, Node*> splitSize(Node*, int);
};

int Node::getSize(Node* node) {
    return !node ? 0 : node->size;
}

void Node::fixSize(Node* node) {
    if (!node) {
        return;
    }
    node->size = getSize(node->right) + getSize(node->left) + 1;
}

Node* Node::merge(Node* node1, Node* node2) {
    if (!node1) {
        return node2;
    }
    if (!node2) {
        return node1;
    }
    if (node1->prior < node2->prior) {
        node1->right = merge(node1->right, node2);
        fixSize(node1);
        return node1;
    } else {
        node2->left = merge(node1, node2->left);
        fixSize(node2);
        return node2;
    }
}

std::pair<Node*, Node*> Node::splitVal(Node* node, int val) {
    if (node == nullptr) {
        return {nullptr, nullptr};
    }
    if (val >= node->value) {
        std::pair<Node*, Node*> parts = splitVal(node->right, val);
        node->right = parts.first;
        fixSize(node);
        return {node, parts.second};
    } else {
        std::pair<Node*, Node*> parts = splitVal(node->left, val);
        node->left = parts.second;
        fixSize(node);
        return {parts.first, node};
    }
}

std::pair<Node*, Node*> Node::splitSize(Node* node, int sz) {
    if (node == nullptr) {
        return {nullptr, nullptr};
    }
    if (sz <= getSize(node->left)) {
        std::pair<Node*, Node*> parts = splitSize(node->left, sz);
        node->left = parts.second;
        fixSize(node);
        return {parts.first, node};
    } else {
        std::pair<Node*, Node*> parts = splitSize(node->right, sz - getSize(node->left) - 1);
        node->right = parts.first;
        fixSize(node);
        return {node, parts.second};
    }    
}

Node* Node::add(Node* node, int val) {
    std::pair<Node*, Node*> parts = splitVal(node, val);
    return merge(merge(parts.first, new Node(val)), parts.second);
}

Node* Node::del(Node* node, int val) { 
    std::pair<Node*, Node*> parts = splitVal(node, val);
    std::pair<Node*, Node*> parts2 = splitVal(parts.first, val-1);
    return merge(parts2.first, parts.second);
}

int Node::getMax(Node*& node, int val) {
    std::pair<Node*, Node*> parts = splitSize(node, getSize(node) - val);
    std::pair<Node*, Node*> parts2 = splitSize(parts.second, 1);
    int ans = parts2.first->value;
    node = merge(parts.first, merge(parts2.first, parts2.second));
    return ans;
}

class Tree{
public:
    Tree();
    void add(int);
    void del(int);
    int getMax(int);
private:
    Node* root;
};  

Tree::Tree() {
    root = nullptr;
}

void Tree::add(int val) {
    root = Node::add(root, val);
}

void Tree::del(int val) {
    root = Node::del(root, val);
}

int Tree::getMax(int val) {
    return Node::getMax(root, val);
}

//////////////////////////

int main() {
    srand(time(0));
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n = 0, c = 0, k = 0;
    cin >> n;
    Tree tree = Tree();
    for (int i = 0; i < n; i++) {
        cin >> c >> k;
        if (c == 1) {
            tree.add(k);
        }
        if (c == -1) {
            tree.del(k);
        }
        if (c == 0) {
            cout << tree.getMax(k) << '\n';
        }
    }
}