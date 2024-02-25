#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<pair<int,int>> queen;
//map<pair<int,int>,int> queens;
bool reg[1000][1000];

bool is_safe(int i,int j,int n){
    for(int ii=0;ii<n;ii++){
        int r1=queen[ii].first;
        int c1=queen[ii].second;
        if((r1==i or c1==j or abs(r1-i)==abs(c1-j)) and r1!=-1 and c1!=-1) return false;
    }
    return true;
}
int main() {
    int n;
    cin>>n;
    if(n<4){
        cout<<"Not possible\n";
        return 0;
    }
    memset(reg,false,sizeof(reg));
    for(int i=0;i<n;i++){
        queen.push_back({-1,-1});   // setting the default position of the queen to be -1,-1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(is_safe(i,j,n) and !reg[i][j]){
                queen[i]={i,j};
                break;
            }else reg[i][j]=false;
        }
         if(queen[i].first==-1 and queen[i].second==-1){ //if we see that the default position of a queen has not been changed meaning the position was either not safe or was rejected;
            reg[queen[i-1].first][queen[i-1].second]=true; // rejecting the current position of the queen of the previous row
            queen[i-1]={-1,-1}; //resetting the position of the previous queen to default;
            i-=2; //to balance out the loop counter;
         }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(queen[i].second==j) cout<<"Q ";
            else cout<<"0 ";
        }
        cout<<"\n";
    } 
    
    return 0;
}
