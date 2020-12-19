#include <iostream>
#include <string>

using std::cin;
using std::cout;

class Node {
public:
    Node(int _value){
        value = _value;// Корректнее писать this->value, если у тебя происходит конфликт имён. А ещё лучше делать ():value(value)...
        height = 1;
        left = nullptr;
        right = nullptr;
    }
    int getValue();
    static Node* insert(Node*, int);// Не очень понял зачем static, если можно было вызываться от текущего объекта. Но ладно
    static bool find(Node*, int);
    static Node* next(Node*, int);
    static Node* prev(Node*, int);
    static Node* del(Node*, int);
    
private:
    int value;
    int height;
    Node* left;
    Node* right;
    static int getHeight(Node*);
    static int getDelta(Node*);
    static void fixHeight(Node*);
    static Node* rotate(Node*);
    static Node* rotateLeft(Node*);
    static Node* rotateRight(Node*);
};

int Node::getValue() {
    return value;
}

int Node::getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    else 
        return node->height;
}

void Node::fixHeight(Node* node) {
    if (node == nullptr) 
        return;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

int Node::getDelta(Node* node) {
    if (node == nullptr)
        return -3;
    return getHeight(node->left) - getHeight(node->right);
}


Node* Node::rotateLeft(Node* node) {
    Node* node2 = node->right;
    node->right = node2->left;
    node2->left = node;
    fixHeight(node);
    fixHeight(node2);
    return node2;
}

Node* Node::rotateRight(Node* node) {
    Node* node2 = node->left;
    node->left = node2->right;
    node2->right = node;
    fixHeight(node);
    fixHeight(node2);
    return node2;
}

Node* Node::rotate(Node* node) { //принимает поддерево node, возвращает хорошее поддерево
    fixHeight(node);
    if (getDelta(node) == -2) {
        if (getDelta(node->right) == 1) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    } else if (getDelta(node) == 2) {
        if (getDelta(node->left) == -1) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    } else {
        return node;
    }
}

Node* Node::insert(Node* node, int val) { //вставляет вершину val в поддерево node и возвр. обновл. поддерево
    if (node == nullptr) {
        return new Node(val);
    }
    if (val == node->value) {
        return node;
    }
    if (val < node->value) {
        node->left = insert(node->left, val);
        return rotate(node);
    }
    if (val > node->value) {
        node->right = insert(node->right, val);
        return rotate(node);
    }
}

Node* Node::del(Node* node, int val) { // удаляет вершину val из поддерева node и возвр. обновл. поддерево 
    if (node == nullptr) {
        return node;
    }
    if (val < node->value) {
        node->left = del(node->left, val);
        return rotate(node);
    }
    if (val > node->value) {
        node->right = del(node->right, val);
        return rotate(node);
    }
    if (val == node->value) {
        if (node->right == nullptr)
            // Здесь утечка памяти, так как ты теряешь ссылку на вершину, взамен которой возвращаешь её левого сына. Переделай
            return node->left;
        Node* min = next(node->right, val);
        Node* newNode = new Node(min->value);
        newNode->left = node->left;
        newNode->right = del(node->right, min->value);// Не очень эффективный алгоритм, так как периодически тебе придётся спускаться
        // и удалять вершины одну за другой по цепочке, пока не найдёшь листик без правого ребёнка. Долго, лучше бы через next получать ссылку и на родителя
        // И сразу менять вершины местами
        delete node;
        return rotate(newNode);
    }
}

bool Node::find(Node* node, int val) {
    if (node == nullptr) { //обязательно проверяем, что непустая вершина
        return false;   
    }
    if (val == node->value) {
        return true;
    }
    if (val < node->value) {
        return find(node->left, val);
    }
    if (val > node->value) {
        return find(node->right, val);
    }
}

Node* Node::next(Node* node, int val) { //возвращает искомую вершину (>val) в поддереве node
    if (node == nullptr) {
        return nullptr;
    }
    if (val >= node->value) {
        return next(node->right, val);
    } else {
        Node* nxt = next(node->left, val);
        if(nxt == nullptr)
            return node;
        else
            return nxt;
    }
}

Node* Node::prev(Node* node, int val){
    if (node == nullptr) {
        return nullptr;
    }
    if (val <= node->value) {
        return prev(node->left, val);
    } else {
        Node* prv = prev(node->right, val);
        if(prv == nullptr)
            return node;
        else
            return prv;
    }
}
/////////////////////////////////

class Tree {
public:
    Tree(){
        root = nullptr;
    }
    void insert(int);
    void del(int);
    bool exists(int);
    Node* next(int);
    Node* prev(int);
private:
    Node* root;
};

void Tree::insert(int val) {
    root = Node::insert(root, val);
}

void Tree::del(int val) {
    root = Node::del(root, val);
}

bool Tree::exists(int val) {
    return Node::find(root, val);
}

Node* Tree::next(int val) {
    return Node::next(root, val);
}

Node* Tree::prev(int val) {
    return Node::prev(root, val);
}

////////////////////////////////

int main() {
    std::string s;
    int x;
    Tree tree = Tree();
    while (cin >> s) {
        cin >> x;
        if (s == "insert") {
            tree.insert(x);
        } else if (s == "next") {
            Node* node = tree.next(x);
            if (node == nullptr) {
                cout << "none\n";
            } else {
                cout << node->getValue() << "\n";
            }
        } else if (s == "prev") {
            Node* node = tree.prev(x);
            if (node == nullptr) {
                cout << "none\n";
            } else {
                cout << node->getValue() << "\n";
            }
        } else if (s == "delete") {
            tree.del(x);
        } else if (s == "exists") {
            if (tree.exists(x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
    }
}
