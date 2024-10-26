#include <bits/stdc++.h>
using namespace std;

map<string, int> m;
char *ca = new char[65];
char *cb = new char[65];
int la = 0;
int lb = 0;

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

int power(int a, int b){
    int res = 1;
    while (b){
        if (b & 1){
            res *= a;
        }
        b >>= 1;
        a *= a;
    }
    return res;
}

int dfs2(int a, int b){
    if (a < 10 || b < 10) {
        return a * b; // Base case for single-digit multiplication
    }
    snprintf(ca, sizeof(ca), "%d", a);
    snprintf(cb, sizeof(cb), "%d", b);
    string sa = ca;
    string sb = cb;
    string str = sa + "_" + sb;
    auto it = m.find(str);
    if (it != m.end()) return m[str];
    la = sa.length();
    lb = sb.length();
    int n = max(la, lb);
    int half = n / 2;
    int w = 0;
    int x = 0;
    int ha = la / 2;
    int hb = lb / 2;
    if (la & 1){
        char *t = ca;
        int i=0, j=ha-1;
        while (i!=ha){
            int tmp = *t - '0';
            tmp *= power(10, j);
            w += tmp;
            t++;
            i++;
            j--;
        }
        i = 0;
        j = ha;
        while (i!=ha+1){
            int tmp = *t - '0';
            tmp *= power(10, j);
            x += tmp;
            t++;
            i++;
            j--;
        }
    } else {
        char *t = ca;
        int i=0, j=ha-1;
        while (i!=ha){
            int tmp = *t - '0';
            tmp *= power(10, j);
            w += tmp;
            t++;
            i++;
            j--;
        }
        i = 0;
        j = ha - 1;
        while (i!=ha){
            int tmp = *t - '0';
            tmp *= power(10, j);
            x += tmp;
            i++;
            j--;
            t++;
        }
    }

    int y = 0;
    int z = 0;
    if (lb & 1){
        char *t = cb;
        int i=0, j=hb-1;
        while (i!=hb){
            int tmp = *t - '0';
            tmp *= power(10, j);
            y += tmp;
            t++;
            i++;
            j--;
        }
        i = 0;
        j = hb;
        while (i!=hb+1){
            int tmp = *t - '0';
            tmp *= power(10, j);
            z += tmp;
            i++;
            j--;
            t++;
        }
    } else {
        char *t = cb;
        int i=0, j=hb-1;
        while (i!=hb){
            int tmp = *t - '0';
            tmp *= power(10, j);
            y += tmp;
            t++;
            i++;
            j--;
        }
        i = 0;
        j = hb - 1;
        while (i!=hb){
            int tmp = *t - '0';
            tmp *= power(10, j);
            z += tmp;
            i++;
            j--;
            t++;
        }
    }
    int res = dfs2(w, y) * static_cast<int>(pow(10, 2*half)) + (dfs2(w+x, y+z) - dfs2(w, y) - dfs2(x, z)) * static_cast<int>(pow(10, half)) + dfs2(x, z);
    m[str] = res;
    return res;
}

int main(){
    int a = 1234;
    int b = 567;
    int c = a * b;
    cout << c << endl;
    int d = dfs2(a, b);
    cout << d << endl;
    return 0;
}