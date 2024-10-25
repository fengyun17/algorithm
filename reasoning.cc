#include <bits/stdc++.h>
using namespace std;

template <typename T> struct node{
    bool leaf;
    node<T> *parent;
    node<T> *skip;
    T data;
    std::deque<node<T>*> chs;
    node(T&& d=nullptr){
        data = std::move(d);
        leaf = false;
        parent = nullptr;
        skip = nullptr;
    }
};

template <typename T, typename U> struct edge;

template <typename T, typename U> struct vertex : public node<T>{
    int id;
    int in;
    int out;
    std::deque<edge<T, U>*> adj;
    vertex(int i) : id(i), in(0), out(0){}
};

template <typename T, typename U> struct edge{
    U data;
    vertex<T, U> *f;
    vertex<T, U> *t;
    edge(U&& d, vertex<T, U> *from, vertex<T, U> *to) : f(from), t(to){
        data = std::move(d);
    }
};

template <typename T> class ToT{
public:
    int cnt;
    bool (*eq)(T, T);
    bool (*com)(T, T);
    node<T> *root;
    node<T> *hot;
    ToT(bool (*e)(T, T), bool (*c)(T, T)) : cnt(0), hot(nullptr) {
        eq = e;
        com = c;
        root = new node<T>;
    }
    ~ToT(){
        delete root; root = nullptr;
    }
    [[nodiscard]] int size() const {return cnt;}
    [[nodiscard]] bool empty() const {return !root ? false : true;}
};

template <typename T, typename U> class graph{
public:
    std::unordered_map<int, vertex<T, U>*> ns;
    std::unordered_set<edge<T, U>*> es;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}