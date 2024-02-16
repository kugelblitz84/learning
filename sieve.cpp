#include <bits/stdc++.h>
using namespace std;

vector<int> generate(int n){
    vector<bool> arr(n+1,true);
    arr[1]=false;
    vector<int> ans={2};
    for(int i=3;i*i<=n;i+=2){
        if(arr[i]){
            for(int j=i*i;j<=n;j+=i) arr[j]=false;
        }
        
    }
    for(int i=3;i<=n;i+=2){
        if(arr[i]) ans.push_back(i); 
    }
    return ans;
}
int main() {
    int t=1;
    //cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> arr=generate(n);
        for(auto i:arr) cout<<i<<" ";
    }
}
