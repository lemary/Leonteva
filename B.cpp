#include <iostream>
#include <string>

using std::cin;
using std::cout;

class Node {
public:
    Node(int _value){
        value = _value;
        sum = _value;
        left = nullptr;
        right = nullptr;
    }
    static Node* insert(Node*, int);
    static long long get_sum(Node*&, int, int);
private:
    int value;
    long long sum;
    Node* left;
    Node* right;
    static std::pair<Node*, Node*> split(Node*, int);// И всё же, зачем статик, если этот функционал по хорошему должен быть в Tree? Или это...
    static Node* merge(Node*, Node*);
    static Node* splay(Node*, int);
    static Node* rotateLeft(Node*);
    static Node* rotateRight(Node*);
    static int find_max(Node*);
    static long long get_node_sum(Node*);
    static void fix_sum(Node*); 
};

long long Node::get_node_sum(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->sum;
    }
}

void Node::fix_sum(Node* node) {
    if (node == nullptr) {
        return;
    } else {
        node->sum = node->value + get_node_sum(node->left) + get_node_sum(node->right);
    }
}

Node* Node::rotateLeft(Node* node) {
    Node* node2 = node->right;
    node->right = node2->left;
    node2->left = node;
    fix_sum(node);
    fix_sum(node2);
    return node2;
}

Node* Node::rotateRight(Node* node) {
    Node* node2 = node->left;
    node->left = node2->right;
    node2->right = node;
    fix_sum(node);
    fix_sum(node2);
    return node2;
}

/*Node* Node::splay(Node* node, int val) { // находит х и в корень дерева 
    if (node == nullptr || node->value == val)  
        return node;  
    if (node->value > val) {   
        if (node->left == nullptr) 
            return node;  
        if (node->left->value > val) {  
            node->left->left = splay(node->left->left, val);
            //fix_sum(node->left);
            //fix_sum(node);
            node = rotateRight(node);  
        } else if (node->left->value < val) {  
            node->left->right = splay(node->left->right, val);
            //fix_sum(node->left);
            //fix_sum(node);
            if (node->left->right != nullptr)  
                node->left = rotateLeft(node->left);
            //fix_sum(node);  
        }  
        return (node->left == nullptr)? node: rotateRight(node);  
    } else {  
        if (node->right == nullptr) 
            return node;  
        if (node->right->value > val) {  
            node->right->left = splay(node->right->left, val);
            //fix_sum(node->right);
            //fix_sum(node);  
            if (node->right->left != nullptr)  
                node->right = rotateRight(node->right);
            //fix_sum(node);  
        } else if (node->right->value < val) {   
            node->right->right = splay(node->right->right, val);
            //fix_sum(node->right);
            //fix_sum(node);  
            node = rotateLeft(node);  
        }  
        return (node->right == nullptr)? node: rotateLeft(node);  
    }  
}*/

Node* Node::splay(Node* node, int val) {
    if (node == nullptr || node->value == val) {
        return node;
    } else if (val < node->value) {
        node->left = splay(node->left, val);
        node = rotateRight(node);
    } else {
        node->right = splay(node->right, val);
        node = rotateLeft(node);
    }
    return node;
}

std::pair<Node*, Node*> Node::split(Node* node, int x) {
    if (node == nullptr) {
        return {nullptr, nullptr};
    }
    if (x >= node->value) {
        std::pair<Node*, Node*> parts = split(node->right, x);
        node->right = parts.first;
        fix_sum(node);
        return {node, parts.second};
    } else {
        std::pair<Node*, Node*> parts = split(node->left, x);
        node->left = parts.second;
        fix_sum(node);
        return {parts.first, node};
    }
}

int Node::find_max(Node* node) {
    if (node->right == nullptr) {
        return node->value;
    } else {
        return find_max(node->right);
    }
}

Node* Node::merge(Node* node1, Node* node2) {
    if (node1 == nullptr) {
        return node2;
    } else {
        node1 = splay(node1, find_max(node1));
        node1->right = node2;
        fix_sum(node1);
        return node1;
    }
}

Node* Node::insert(Node* node, int val) { //вставляет вершину val в поддерево node и возвр. обновл. поддерево
    std::pair<Node*, Node*> parts = split(node, val);
    if (parts.first != nullptr && find_max(parts.first) == val) {
        return merge(parts.first, parts.second);
    } else {
        return merge(merge(parts.first, new Node(val)), parts.second);
    }
}

long long Node::get_sum(Node*& node, int l, int r) {
    std::pair<Node*, Node*> parts1 = split(node, l-1);
    std::pair<Node*, Node*> parts2 = split(parts1.second, r);
    long long ans = get_node_sum(parts2.first);
    node = merge(parts1.first, merge(parts2.first, parts2.second));
    return ans;
}

/////////////////////////////////

class Tree {
public:
    Tree(){
        root = nullptr;
    }
    void insert(int);
    long long sum(int, int);
private:
    Node* root;
};

void Tree::insert(int val) {
    root = Node::insert(root, val);
}

long long Tree::sum(int l, int r) {
    return Node::get_sum(root, l, r);
}


////////////////////////////////

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    const long long inf = 1e17;
    const long long mod = 1e9;
    std::string s;
    char x = 0;
    int n = 0;
    cin >> n;
    Tree tree = Tree();
    long long last = inf;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        if (x == '?') {
            int l = 0, r = 0;
            cin >> l >> r;
            last = tree.sum(l, r);
            cout << last << "\n";
        } else {
            int x;
            cin >> x;
            if (last == inf) {
                tree.insert(x);
            } else {
                tree.insert((x + last) % mod);
                last = inf;
            }
        }
    }
}
