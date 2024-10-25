#include <bits/stdc++.h>
using namespace std;

class node {
public:
    std::string f;
    std::map<std::string, node*> nexts; // 子节点按字典序排序

    node(std::string file) : f(file) {}
};

class solve {
private:
    node* root;

public:
    solve() {
        root = new node("");
    }

    void pbf(std::vector<std::string>& folder) {
        if (folder.empty()) return;
        build(folder);
        dfs(root, 0);
    }

    void build(std::vector<std::string>& folder) {
        for (const auto& path : folder) {
            std::vector<std::string> files;
            std::string current = "";
            for (char ch : path) {
                if (ch == '\\') {
                    files.push_back(current);
                    current.clear();
                } else {
                    current += ch;
                }
            }
            files.push_back(current);

            node* cur = root;
            for (const auto& file : files) {
                if (cur->nexts.find(file) == cur->nexts.end()) {
                    cur->nexts[file] = new node(file);
                }
                cur = cur->nexts[file];
            }
        }
    }

    std::string space(int n) {
        std::string res;
        for (int i = 0; i < n; ++i) {
            res += "  ";
        }
        return res;
    }

    void dfs(node* cur, int level) {
        if (level != 0) {
            std::cout << space(level) << cur->f << std::endl;
        }
        for (const auto& pair : cur->nexts) {
            dfs(pair.second, level + 1);
        }
    }
};

int main(){
    std::vector<std::string> folders = {"C:\\Users\\Documents\\file1.txt", "C:\\Users\\Documents\\file2.txt", "C:\\Users\\Pictures\\photo1.jpg"};
    solve s;
    s.pbf(folders);
    return 0;
}