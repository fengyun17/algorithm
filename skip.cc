#include <bits/stdc++.h>
using namespace std;

class skipList{
public:
    skipList(){
        head = new headNode(1);
    }
    ~skipList(){
        int l = head->level;
        for (int i=0; i<l; i++){
            node *cur = head->next;
            while (cur != nullptr){
                node *t = cur->next;
                delete cur;
                cur = t;
            }
            cur = head;
            head = static_cast<headNode*>(head->down);
            delete cur;
        }
    }
    bool find(int data){
        node *pre = head;
        node *cur = pre->next;
        while (1){
            if (cur != nullptr){
                if (cur->data < data){
                    pre = cur;
                    cur = cur->next;
                    continue;
                } else if (cur->data == data){
                    return true;
                }
            }
            if (pre->down == nullptr) break;
            pre = pre->down;
            cur = pre->next;
        }
        return false;
    }
    void add(int data){
        if (find(data)) return;
        int l = get();
        if (l > head->level){
            l = head->level + 1;
            headNode *h = new headNode(l);
            h->down = head;
            head = h;
        }
        //创建l层的data数据(列复制)
        node **list = new node * [l];
        for (int i=l-1; i>=0; i--){
            list[i] = new node(data);
            if (i < l-1){
                list[i]->down = list[i+1];
            }
        }
        node *h = head;
        for (int i=head->level; i>l; i--){
            h = h->down;
        }
        node *pre = h;
        node *cur = pre->next;
        for (int i=0; i<l; i++){
            while (cur!=nullptr && cur->data<data){
                pre = cur;
                cur = cur->next;
            }
            list[i]->next = cur;
            pre->next = list[i];
            pre = pre->down;
            if (pre != nullptr) cur = pre->next;
        }
        delete []list;
        list = nullptr;
    }
    void del(int data){
        node *pre = head;
        node *cur = pre->next;
        while (1){
            if (cur != nullptr){
                if (cur->data < data){
                    pre = cur;
                    cur = cur->next;
                    continue;
                } else if (cur->data == data){
                    pre->next = cur->next;
                    delete cur;
                }
            }
            if (pre->down == nullptr) break;
            pre = pre->down;
            if (head->next == nullptr){
                delete head;
                head = static_cast<headNode*>(pre);
            }
            cur = pre->next;
        }
    }
    void show() const{
        node *h = head;
        while (h != nullptr){
            node *cur = h->next;
            while (cur != nullptr){
                cout << cur->data << " ";
                cur = cur->next;
            }
            cout << endl;
            h = h->down;
        }
        cout << endl;
    }
private:
    struct node{
        int data;
        node *next;
        node *down;
        node(int d = int()) : data(d), next(nullptr), down(nullptr){}
    };
    struct headNode : public node{
        int level;
        headNode(int l) : level(l){}
    };
    headNode *head;

    int get() const{
        int l = 1;
        while (rand() % 2 == 1) l++;
        return l;
    }
};

int main(){
    skipList sl;
    srand(time(nullptr));
    cout << rand() << endl;
    for (int i=0; i<20; i++){
        sl.add(rand() % 100);
    }
    sl.add(50);
    sl.show();
    sl.del(50);
    sl.show();
    return 0;
}