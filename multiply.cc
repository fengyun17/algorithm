#include <bits/stdc++.h>
using namespace std;

map<string, int> m;

int dfs(int a, int b){
    string str = to_string(a) + '_' + to_string(b);
    auto it = m.find(str);
    if (it != m.end()) return m[str];
    if (a < 10 || b < 10) {
        return a * b; // Base case for single-digit multiplication
    }
    int n = max(to_string(a).length(), to_string(b).length());
    int half = n / 2;
    int w = a / pow(10, half);
    int x = a % (int)pow(10, half);
    int y = b / pow(10, half);
    int z = b % (int)pow(10, half);
    int res = dfs(w, y) * static_cast<int>(pow(10, 2*half)) + (dfs(w+x, y+z) - dfs(w, y) - dfs(x, z)) * static_cast<int>(pow(10, half)) + dfs(x, z);
    m[str] = res;
    return res;
}

int main(){
    int a = 1234;
    int b = 5678;
    int c = a * b;
    cout << c << endl;
    int d = dfs(a, b);
    cout << d << endl;
    return 0;
}