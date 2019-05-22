#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second

const ll maxn=100001;
ll blksz=333;
ll n,m;
ll val[maxn];
vector<int> adj[maxn];
int szomsz[maxn];

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) {
		cin>>val[i];
	}
	set<pair<int,int>> edgs;
	vector<pair<int,int>> lst;
	for(int i=0;i<m;++i) {
		int a,b;
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
		edgs.insert({min(a,b),max(a,b)});
		lst.push_back({min(a,b),max(a,b)});
	}
	
	map<array<int,3>, ll> kell;
	for(int i=1;i<=n;++i) {
		//cerr<<i<<" "<<sz(adj[i])<<"FOK\n";
		if(sz(adj[i])<=blksz) {
			for(int j=0;j<sz(adj[i]);++j) {
				for(int k=j+1;k<sz(adj[i]);++k) {
					int a=adj[i][j], b=adj[i][k];
					if(a>b) swap(a,b);
					if(edgs.count({a,b})) {
						array<int,3> ind={i,a,b};
						sort(ind.begin(), ind.end());
				//		cerr<<ind[0]<<" "<<ind[1]<<" "<<ind[2]<<" "<<val[i]<<"\n";
						if(kell.count(ind)==0) kell[ind]=val[i];
						else {
							kell[ind]=max(kell[ind], val[i]);
						}
					}
				}
			}
		}else {
			for(int j=0;j<sz(adj[i]);++j) {
				szomsz[adj[i][j]]=1;
			}
			
			for(int j=0;j<sz(lst);++j) {
				if(szomsz[lst[j].xx]&&szomsz[lst[j].yy]) {
					array<int,3> ind={i,lst[j].xx,lst[j].yy};
					sort(ind.begin(), ind.end());
					if(kell.count(ind)==0) kell[ind]=val[i];
					else {
						kell[ind]=max(kell[ind], val[i]);
					}
				}
			}
			
			for(int j=0;j<sz(adj[i]);++j) {
				szomsz[adj[i][j]]=0;
			}
		}
	}
	
	ll ans=0;
	for(auto i:kell) {
	//	cerr<<i.xx[0]<<" "<<i.xx[1]<<" "<<i.xx[2]<<" -> "<<i.yy<<"\n";
		ans+=i.yy;
	}
	
	cout<<ans<<"\n";
		
	return 0;
}
