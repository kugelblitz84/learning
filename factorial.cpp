#include <bits\stdc++.h>
//#define int long long
using namespace std;
string add(string first,string sec){
    //cout<<(sec.size()<first.size());
    int diff = abs((int)first.size()-(int)sec.size());
    string leading_zero(diff,'0');
    first.size() < sec.size() ? first = leading_zero + first : sec = leading_zero + sec;
    string ans = "";
    int res = 0,car = 0;
    for(int i= first.size()-1;i>=0; i--){
        res = (first[i] -'0') + (sec[i] - '0') + car;
        car = res/10;
        res %= 10;
        char tmp = '0' + res;
        ans =  tmp + ans;
    }
    if(car) {
        char temp = '0' + car;
        ans = temp + ans;
    }
    return ans;
}
string mult(string s1,string s2){
    string ans = "";
    string trail_zero = "";
    for(int i=s2.size()-1 ;i>=0 ;i--){
        int res = 0,carry = 0;
        string temp = "";
        for(int j=s1.size()-1;j>=0;j--){
            res = ((s2[i] - '0')*(s1[j] - '0')) + carry ;
            carry = res / 10;
            res %= 10;
            char result = '0' + res;
            temp = result + temp;
        }
        if(carry){
            char car = '0' + carry;
            temp = car + temp;
        }
        if(i == s2.size()-1) ans = temp;
        else {
            temp = temp + trail_zero;  
            ans = add(temp ,ans );
        }
        trail_zero += "0";
    }
    return ans;
}

string fact(int n){
    if(n == 1) return "1";
     string s = to_string(n);
    return mult(s,fact(n-1));
}
void solve(){
    
    int n;
    cin>>n;
    cout<<fact(n);
    // string s1,s2;
    // cin>>s1>>s2;
    // //s1<<s2;
    // cout<<mult(s1,s2);
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin>>t;
    while(t--) solve();
    return 0;
}
