#include <bits/stdc++.h>
using namespace std;

int* pre(const char *s){
	int m = (int)strlen(s);
	int j=0;
	int *next = new int[m];
	int t = next[0] = -1;
	while (j < m-1){
		if (t<0 || s[j]==s[t]){
			j++;
			t++;
			next[j] = s[j]!=s[t] ? t : next[t];
		} else {
			t = next[t];
		}
	}
	return next;
}

void match(const char *t, const char *s, vector<int> &res){
	int *dp = pre(s);
	int i=0, j=0;
	int n = (int)strlen(t);
	int m = (int)strlen(s);
	while (i<n){
		if (j<0 || t[i]==s[j]){
			i++;
			j++;
		} else {
			j = dp[j];
		}
		if (j == m - 1 && t[i]==s[j]){
			res.push_back(i-j);
		}
	}
}

int main(){
    const char *s = "iss";
    const char *t = "absississssissisisssisskkisskjiss";
    vector<int> res;
    match(t, s, res);
    for (int i=0; i<res.size(); i++){
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}