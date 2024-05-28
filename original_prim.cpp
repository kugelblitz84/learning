#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int,int>>> adj_list(1000);
vector<int> current_weight(1000,1000);

vector <pair<int,int>> prim(int n,int size){
	vector<int> parent(size);
	parent[n]=-1;
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	pq.push({0,n});
	while(!pq.empty()){
		int least_cost=pq.top().second;
		pq.pop();
		for(auto i:adj_list[least_cost]){
			if(current_weight[i.second]>i.first){
				pq.push({i.first,i.second});
				parent[i.second]=least_cost;
				current_weight[i.second]=i.first;
			}
		}
	}
	vector<pair<int,int>> ans;
	for(int i=1;i<size;i++){
		ans.push_back({parent[i],i});
	}
	return ans;
}
void solve(){
	int n;
	cout<<"enter number of vertex: ";
	cin>>n;
	int adj_mat;
	cout<<"enter adjecancy matrix: \n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>adj_mat;
			if(i!=j) adj_list[i].push_back({adj_mat,j});
		}
	}
	vector<pair<int,int>> mst=prim(0,n);
	int cost=0;
	for(auto i:mst){
		cout<<i.first<< " "<<i.second<<endl;
		cost+=current_weight[i.second];
	}
	cout<<cost;

}
int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t=1;
	//cin>>t;
	while(t--) solve();
	return 0;
}
