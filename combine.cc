#include <bits/stdc++.h>
using namespace std;

class node {
public:
    std::set<int> kinds;
    int cnts[10000];

    node() : cnts{0} {} // Initialize cnts to zero
};

struct myHash {
    size_t operator()(const node& p) const {
        int h = 0;
        for (int i = 0; i < 10000; i++) {
            h = (h << 5) ^ (h >> 27); // Changed to XOR for mixing
            h += p.cnts[i];
        }
        for (const auto &kind : p.kinds) {
            h ^= std::hash<int>()(kind) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return (size_t) h;
    }
};

struct myequal{
    bool operator()(const node &a, const node &b){
        if (a.kinds.size() != b.kinds.size()) {
            return false;
        } else {
            for (int i = 0; i < 10000; i++) {
                if (a.cnts[i] != b.cnts[i]) return false;
            }
            return true;
        }
    }
};

node path;
unordered_set<node, myHash, myequal> s;
vector<node> res;
int cnt = 0;
void dfs(int x){
    if (x == 0){
        if (s.find(path) == s.end()){
            res.push_back(path);
            s.insert(path);
            cnt++;
        }
    } else {
        for (int i=1; i<=x; i++){
            if (i%2==1){
                path.kinds.insert(i);
                path.cnts[i]++;
                dfs(x-i);
                path.cnts[i]--;
                if (path.cnts[i] == 0) path.kinds.erase(i);
            }
        }
    }
}

int main(){
    dfs(9);
    cout << cnt<< endl;
    for (int i=0; i<res.size(); i++){
        for (int j=0; j<10; j++){
            if (res[i].cnts[j] != 0){
                cout << j << "----" << res[i].cnts[j] << " ";
            }
        }
        cout << endl;
    }
    return 0;
}