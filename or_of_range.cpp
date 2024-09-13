#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#define int long long
using namespace std;
void solve(){
    int l , r;
    cin>>l>>r;
    int ans = 0;
    int range=r-l+1;
    for(int i=0;i<31;i++){
        bool set_ith=0;
        if(range > (1<<i)) set_ith=1;
        else if(l/(1<<i) == r/(1<<i)) {
            set_ith = ((l/(1<<i))&1);
        }
        else {
            set_ith=1;
        }
        ans |= (set_ith<<i);
    }
    cout<<ans<<"\n";
}

int32_t main() {
    //memset(dp,-1,sizeof(dp));
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
