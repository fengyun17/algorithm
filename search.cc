#include <bits/stdc++.h>
using namespace std;

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

    char *trim(char *w){
        int i = 0;
        while (w[i] != '\0'){
            if (w[i]==' ' || w[i]=='\t' || w[i]=='\n'){
                i++;
            } else break;
        }
        int j = i;
        while (w[j] != '\0'){
            if (w[j]==' ' || w[j]=='\t' || w[j]=='\n'){
                break;
            }
            j++;
        }
        w[j] = '\0';
        return w + i;
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
                char *w = strtok(ls, "|");
                while (w != nullptr){
                    w = trim(w);
                    if (strlen(w) > 0){
                        words.emplace_back(w);
                    }
                    w = strtok(nullptr, "|");
                }
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
        char *w = strtok(ps, "|");
        while (w != nullptr){
            w = trim(w);
            if (strlen(w) > 0){
                ws.emplace_back(w);
            }
            w = strtok(nullptr, "|");
        }
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
    indexs ids;
    ids.set(".cc");
    ids.create("/Users/guozhi/Desktop/rwys/cs");
    vector<iterm> ans = ids.query("int和char是类方法，还有res");
    for (int i=0; i<ans.size(); i++){
        cout << ans[i].id << " " << ans[i].freqs << endl;
    }
    return 0;
}