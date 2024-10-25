#include <bits/stdc++.h>
using namespace std;

void mergeSort(int l, int r, vector<int> &a, int &cnt){
    if(l==r) return;
	int mi = (l+r)>>1;
	mergeSort(l, mi, a, cnt);
	mergeSort(mi+1, r, a, cnt);
	int b=mi-l;
	vector<int> B(b+1);
	for(int i=0; i<=b; B[i]=a[i+l], i++);
	for(int p=l, i=0, q=mi+1; i<=b;){
		if((q<=r) && (B[i]>a[q])){
			cnt+=b-i+1;
			a[p++] = a[q++];
		}
		if((q>r) || (B[i]<=a[q])){
			a[p++] = B[i++];
		}
	}
}

int main(){
    vector<int> a;
    a.push_back(2);
    a.push_back(7);
    a.push_back(3);
    a.push_back(4);
    a.push_back(1);
	a.push_back(5);
    int cnt = 0;
    mergeSort(0, 5, a, cnt);
    cout << cnt << endl;
	for (int i = 0; i < a.size(); ++i){
		cout << a[i] << " ";
	}
	cout << endl;
    return 0;
}