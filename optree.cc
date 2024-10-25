#include <bits/stdc++.h>
using namespace std;

double dp[100][100], w[100][100];
int s[100][100];
void solve(double p[], double q[], int n){
    for (int i=0; i<=n; i++){
        w[i+1][i] = q[i];
		s[i][i] = i;
    }

    for (int i=1; i<=n; i++){
        for (int j=i+1; j<=n; j++){
            dp[i][j] = 1e18;
        }
    }

    for (int l=1; l<=n; l++){
        for (int i=1; i+l-1<=n; i++){
            int j = i + l - 1;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            for (int k=s[i][j-1]; k<=s[i+1][j]; k++){
                double t = dp[i][k-1] + dp[k+1][j];
                if (t < dp[i][j] && fabs(t - dp[i][j])>1E-6){  
                    dp[i][j] = t;
                    s[i][j] = k;
                }
            }
            dp[i][j] += w[i][j];
        }
    }
}

struct node
{
    int key;
    node *r, *l;
    node(){
        l = NULL;
        r = NULL;
    }
};

void show(node *root, int level){
    if (root == NULL) return;
    show(root->r, level+1);
    for (int i=0; i<level; i++){
        printf("   ");
    }
    printf("%d\n", root->key);
    show(root->l, level+1);    
}

void print(node *root){
    show(root, 0);
}

void dfs(int n, int i, int j, node **root){
    node *cur;
    int k = s[i][j];
    if (k > 0){
        cur = new node();
        cur->key = k;
        *root = cur;
        int t = k - 1;
        if (t>=i && t<=n){
            dfs(n, i, t, &(*root)->l);
        }
        t = k + 1;
        if (t <= j){
            dfs(n, t, j, &(*root)->r);
        }
    }
}

int main(){
    int n = 5;
    double p[] = {0,0.15,0.1,0.05,0.1,0.2};
    double q[] = {0.05,0.1,0.05,0.05,0.05,0.1};
    node *root = NULL;
    solve(p, q, n);
    dfs(n, 1, n, &root);
    print(root);
    return 0;
}
