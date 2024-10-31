#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;

#define x first
#define y second
typedef pair<int, int> pii;

bool isWhitespace(char ch) {
    return std::isspace(static_cast<unsigned char>(ch)) != 0;
}

bool isChinese(char c) {
    int code = static_cast<int>(c);
    return code >= 0x4E00 && code <= 0x9FA5;
}

bool isNumber(char c) {
    int code = static_cast<int>(c);
    return code >= 0x30 && code <= 0x39;
}

bool isEnglish(char c){
    return isalpha(c);
}

std::set<char> s{'-', '_', '/', '+', '=', '.', ',', '*', '$', '%', '(', ')', '[', ']', '{', '}'};

char *trim(char *w){
    int i = 0;
    while (w[i] != '\0'){
        if (w[i]==' ' || w[i]=='\t' || w[i]=='\n'){
            i++;
        } else break;
    }
    int j = i;
    while (w[j] != '\0'){
        if (w[j]=='\t' || w[j]=='\n'){
            break;
        }
        j++;
    }
    w[j] = '\0';
    return w + i;
}

string sub = "";
const int N = 100;
const int M = 1000;
int head[N]={0}, nber[M]={0}, to[M]={0}, q[N], dist[N];
bool type[N], isw[N];
int idx = 0, cnt = 0, l = 0, r = 0, n;
nlohmann::json dict;
map<pii, string> m;
vector<int> fa[N];
vector<string> path;
vector<string> res[10];

void add(int u, int v){
    cnt++;
	nber[cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt;
}

bool match(string str){
    try {
        int tmp = dict[str];
        return true;
    } catch (exception &e){
        return false;
    }
}

void init(){
    fill(dist, dist + 100, numeric_limits<int>::max());
    ifstream ifs("/Users/guozhi/Desktop/rwys/cs/words.json");
    ifs >> dict;
    ifs.close();
}

void read(char *str, vector<string> &words){
    char *w = strtok(str, "|");
    while (w != nullptr){
        w = trim(w);
        if (strlen(w) > 0){
            if (static_cast<unsigned char>(*w) >= 0x80) type[idx] = true;
            words.emplace_back(w);
            idx++;
        }
        w = strtok(nullptr, "|");
    }
    idx = 0;
    n = words.size();
    for (int i=0; i<n; i++){
        add(i, i+1);
        if (type[i]){
            if (match(words[i])){
                isw[i] = true;
                m.insert({{i, i+1}, words[i]});
            } else {
                if (words[i]=="，" || words[i]=="。" || words[i]=="！" || words[i]=="？"){
                    m.insert({{i, i+1}, words[i]});
                }
            }
        } else {
            m.insert({{i, i+1}, words[i]});
        }
    }
    for (int i=0; i<n; i++){
        if (type[i]){
            sub = "";
            sub += words[i];
            for (int j=i+1; j<n && j<=i+5; j++){
                sub += words[j];
                if (match(sub)){
                    add(i, j+1);
                    m.insert({{i, j+1}, sub});
                }
            }
            sub = "";
        }
    }
}

void bfs(){
	q[r++] = 0;
	fa[0].push_back(0);
	dist[0] = 0;
	while (l < r){
		int cur = q[l++];
		for (int e=head[cur]; e!=0; e=nber[e]){
			if (dist[to[e]] > dist[cur] + 1){
				q[r++] = to[e];
				dist[to[e]] = dist[cur] + 1;
                if (fa[to[e]].empty()){
				    fa[to[e]].push_back(cur);
                } else {
                    fa[to[e]].clear();
                    fa[to[e]].push_back(cur);
                }
			} else if (dist[to[e]] == dist[cur] + 1){
                q[r++] = to[e];
				dist[to[e]] = dist[cur] + 1;
                fa[to[e]].push_back(cur);
            }
		}
	}
}

void dfs(int u){
	for (int f : fa[u]){
		if (f == u){ 
			res[idx++] = path;
            if (idx > 1){
                //sudo(语法检查)
                cout << "语法检查" << endl;
            }
			return;
		}
		auto ret = m.find({f, u});
		if (ret != m.end()){
			path.push_back(ret->y);
		} else {
            path.push_back("no");
            return;
        }
		dfs(f);
        path.pop_back();
	}
}

void split(char *str, vector<string> &words){
    read(str, words);
    bfs();
    dfs(n);
    words.clear();
    for (int i=res[0].size()-1; i>=0; i--){
        if (res[0][i]!="，" && res[0][i]!="。" && res[0][i]!="！" || res[0][i]!="？"){
            words.emplace_back(res[0][i]);
        }
    }
    m.clear();
    path.clear();
    sub = "";
    memset(res, 0, sizeof(res));
    memset(dist, 1e16, sizeof(dist));
    memset(fa, 0, sizeof(fa));
    memset(type, false, sizeof(type));
    memset(head, 0, sizeof(head));
    memset(to, 0, sizeof(to));
    memset(nber, 0, sizeof(nber));
    memset(q, 0, sizeof(q));
    cnt=0, n=0, r=0, l=0, idx=0;
}

struct iterm{
    string id;
    int freqs;
    list<int> locs;
    iterm(string i, int f, int pos) : id(i), freqs(f){
        locs.emplace_back(pos);
    }
    bool operator==(const iterm &o) const{
        return id == o.id;
    }
    bool operator!=(const iterm &o) const{
        return id != o.id;
    }
    bool operator<(const iterm &o) const{
        return id < o.id;
    }
};

class ilist{
private:
    list<iterm> its;
public:
    void add(string id, int pos){
        for (auto &t : its){
            if (t.id == id){
                t.freqs++;
                t.locs.emplace_back(pos);
                return;
            }
        }
        its.emplace_back(id, 1, pos);
    }
    const list<iterm>& get() const{
        return its;
    }
};

class indexs{
private:
    list<string> flist;
    unordered_map<string, ilist> imap;
    string suffix;

    char *seg(char *str){
        char *p1 = new char[100];
        char *p2 = p1;
        int cnt = 0;
        bool f = false;
        while (*str != '\0'){
            if (static_cast<unsigned char>(*str) >= 0x80) {
                if (cnt!=0 && f) *p2++ = '|';
                *p2++ = *str++;
                *p2++ = *str++;
                *p2++ = *str++;
                *p2++ = '|';
                f = false;
                cnt++;
            } else if (isEnglish(*str)) {
                *p2++ = *str++;
                f = true;
                cnt++;
            } else if (isWhitespace(*str)){
                if (cnt == 0){
                    *str++;
                } else {
                    *p2++ = *str++;
                    f = true;
                    cnt++;
                }
            } else if (isNumber(*str)){
                *p2++ = *str++;
                f = true;
                cnt++;
            } else if (s.find(*str) != s.end()){
                *p2++ = *str++;
                f = true;
                cnt++;
            } else {
                if (cnt!=0 && f) *p2++ = '|';
                *p2++ = *str++;
                *p2++ = *str++;
                *p2++ = *str++;
                *p2++ = '|';
                f = false;
                cnt++;
            }
        }
        *p2 = '\0';
        p2 = nullptr;
        return p1;
    }

    void getAll(string path){
        if (filesystem::exists(path) && filesystem::is_directory(path)) {
            std::cout << "Files in the folder:\n";
            // Iterate through the directory
            for (const auto& entry : filesystem::recursive_directory_iterator(path)) {
                if (filesystem::is_regular_file(entry.status())) {
                    string str = entry.path().string();
                    int idx = str.find(suffix);
                    if (idx!=string::npos && idx+suffix.size()==str.size()){
                        //过滤
                        //std::cout << entry.path() << std::endl;
                        flist.emplace_back(entry.path());
                        
                    }
                }
            }
        }
    }
public:
    void set(string suff){
        suffix = suff;
    }
    void create(string dir){
        getAll(dir);
        for (string &path : flist){
            FILE *pf = fopen(path.c_str(), "r");
            if (pf == nullptr) continue;
            vector<string> words;
            int pos = 0;
            char lines[2048] = {0};
            while (!feof(pf)){
                fgets(lines, 2048, pf);
                char *ls = seg(lines);
                split(ls, words);
                for (string &word : words){
                    pos++;
                    auto it = imap.find(word);
                    if (it == imap.end()){
                        ilist l;
                        l.add(path, pos);
                        imap.emplace(word, l);
                    } else {
                        it->second.add(path, pos);
                    }
                }
            }
            fclose(pf);
        }
    }
    vector<iterm> query(string phrase){
        vector<iterm> ans;
        vector<string> ws;
        char *ps = seg(const_cast<char*>(phrase.c_str()));
        split(ps, ws);
        if (ws.empty()) return {};
        if (ws.size() == 1){
            auto it = imap.find(ws[0]);
            if (it == imap.end()){
                cout << "no" << endl;
                return {};
            } else {
                auto my = it->second.get();
                for (auto &mm : my){
                    ans.emplace_back(mm);
                }
                return ans;
            }
        } else {
            vector<ilist> res;
            for (int i=0; i<ws.size(); i++){
                auto it = imap.find(ws[i]);
                if (it != imap.end()){
                    res.emplace_back(it->second);
                }
            }
            //求交
            stack<iterm> st;
            stack<iterm> st2;
            vector<iterm> tmp;
            int time = 0;
            vector<iterm> v1(res[0].get().begin(), res[0].get().end());
            for (int i=1; i<res.size(); i++){
                vector<iterm> v2(res[i].get().begin(), res[i].get().end());
                //保证v1, v2有序
                sort(v1.begin(), v1.end());
                sort(v2.begin(), v2.end());
                set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(tmp));
                for (int j=0; j<tmp.size(); j++){                   
                    if (st.empty()){
                        st.emplace(tmp[j]);
                    } else {
                        st2.emplace(tmp[j]);
                        while (!st.empty()){
                            if (st.top() != tmp[j]){
                                st2.emplace(st.top());
                            }
                            st.pop();
                        }
                        swap(st, st2);
                        time++;
                    }
                    
                }
                v1.swap(tmp);
                tmp.clear();
            }
            
            if (time % 2 == 1){
                while (!st.empty()){
                    st2.emplace(st.top());
                    st.pop();
                }
                swap(st, st2);
            }
            
            while (!st.empty()){
                ans.emplace_back(st.top());
                st.pop();
            }
            vector<iterm> ans2;
            for (int i=0; i<ans.size(); i++){
                ans2.emplace_back(ans[i]);
            }
            for (int i=0; i<res.size(); i++){
                vector<iterm> v(res[i].get().begin(), res[i].get().end());
                sort(v.begin(), v.end());
                auto en = unique(v.begin(), v.end());
                v.erase(en, v.end());
                for (int k=0; k<v.size(); k++){
                    bool flag = false;
                    for (int j=0; j<ans.size(); j++){
                        if (ans[j] == v[k]){
                            flag = true;
                        }
                    }
                    if (!flag){
                        ans2.emplace_back(v[k]);
                    }
                }
            }
            return ans2;
        }
    }
};

int main(){
    init();
    indexs ids;
    ids.set(".txt");
    ids.create("/Users/guozhi/Desktop/rwys/cs");
    vector<iterm> ans = ids.query("int和char是类方法，还有res");
    for (int i=0; i<ans.size(); i++){
        cout << ans[i].id << " " << ans[i].freqs << endl;
    }
    return 0;
}