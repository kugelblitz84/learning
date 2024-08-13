#include <bits\stdc++.h>
#define int long long
using namespace std;

class trieNode{
private:
    int words_in;
    int ended_here;
    trieNode* node[26];
public:
    void insert(string);
    string search_prefix(string);
    trieNode();
};
trieNode :: trieNode(){
        for(auto &i:node){
            i = nullptr;
        }
        words_in=0;
        //ended_here=0;
}
trieNode *root = new trieNode();

void trieNode :: insert(string s){
        trieNode *temp;
        temp = root;
        for(auto i:s){
            if(temp->node[i-'a'] == nullptr){
                temp->node[i - 'a'] = new trieNode();
            }
            temp = temp->node[i-'a'];
            temp->words_in++;
        }
        //temp->words_in++;
}

string trieNode :: search_prefix(string s){
        string ans = "";
        trieNode *temp;
        temp = root;
        for(int i = 0 ;i<s.size();i++){
            if(temp->node[s[i] - 'a'] == nullptr){
                return "&not_found&";
            }
            temp = temp->node[s[i]-'a'];
        }
        ans = s;
        while(1){
            int max_index = -1,max_words = 0;
            for(int i= 0 ;i<26;i++){
                if(temp->node[i] != nullptr){
                    if(max_words < temp->node[i]->words_in){
                        max_index = i;
                        max_words = temp->node[i]->words_in;
                        //cout<<(char)('a'+i);
                    }
                    //cout<<temp->node[i]->words_in<<endl;

                }
            }
            if(max_index == -1) return ans;
            else ans += ('a'+max_index), temp = temp->node[max_index];
        }
        return ans+"yes";
}

void solve(){
    int n;

    string s;
    trieNode dict;
    getline(cin,s);
    stringstream ss(s);
    string word;
    while (ss >> word) {
        dict.insert(word);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        cout << dict.search_prefix(s) << endl;
    }
}
int32_t main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    //memset(trieNode,0,sizeof(trieNode));
    int t=1;
    //cin>>t;
    while(t--) solve();
    return 0;
}
