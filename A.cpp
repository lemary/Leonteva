#include <iostream>

using std::cin;
using std::cout;

struct Elem {
    int val;
    Elem* prev;
};

struct Stack {
    int size;
    Elem* last;
};

void initStack(Stack* st) {
    st->size = 0;
    st->last = nullptr;
}

bool isEmpty(Stack* st) {
    return (st->size == 0);
}

void push(Stack* st, int Val) {
    Elem* e = new Elem();
    e->val = Val;
    e->prev = st->last;
    st->last = e;
    st->size++;
}

int pop(Stack* st) {
    Elem* last = st->last;
    st->last = last->prev;
    st->size--;
    int value = last->val;
    free(last);
    return value;
}

int back(Stack* st) {
    return (st->last->val);
}

void clear(Stack* st) {
    while (!isEmpty(st)) {
        pop(st);
    }
}

int size(Stack* st) {
    return st->size;
}

int main()
{
    Stack st = Stack();
    initStack(&st);
    std::string s;
    while(cin>>s){
        if(s=="push"){
            int v;
            cin>>v;
            push(&st,v);
            cout<<"ok\n";
        }else if(s=="pop"){
            if(isEmpty(&st)) cout<<"error\n";
            else cout<<pop(&st)<<"\n";
        }else if(s=="back"){
            if(isEmpty(&st)) cout<<"error\n";
            else cout<<back(&st)<<"\n";
        }else if(s=="size"){
            cout<<size(&st)<<"\n";
        }else if(s=="clear"){
            clear(&st);
            cout<<"ok\n";
        }else if(s=="exit"){
            cout<<"bye";
            return 0;
        }
    }
    return 0;
}
