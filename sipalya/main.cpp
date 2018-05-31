/*
ID: noszaly1
TASK: {TASK}
LANG: C++11               
*/

//Noszály Áron 10o Debreceni Fazekas Mihály Gimnázium

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<cassert>
#include<cassert>
#include<unordered_map>
#include<unordered_set>
#include<functional>
#include<queue>
#include<stack>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<sstream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<numeric>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define xx first
#define yy second
#define sz(x) (int)(x).size()
#define gc getchar
#define IO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const double PI=acos(-1);

template<typename T> T getint() {
	T val=0;
	char c;
	
	bool neg=false;
	while((c=gc()) && !(c>='0' && c<='9')) {
		neg|=c=='-';
	}

	do {
		val=(val*10)+c-'0';
	} while((c=gc()) && (c>='0' && c<='9'));

	return val*(neg?-1:1);
}

vector<int> adj[20001], badj[20001];
map<int,int> ord[20001], bord[20001];
map<int,int> iord[20001], ibord[20001];

vector<int> fadj[60501];
int fid=1;

map<pair<int,int>, int> owner;

int b2[20001];



int origin;

void dfs_up(int x, int par) {
	//cerr<<"dfs_up: "<<x<<" "<<par<<"\n";
	
	if(owner[mp(x,par)]) fadj[fid].pb(owner[mp(x,par)]);
	owner[mp(x,par)]=fid;
	
	
	if(x==origin) return ;
	
	dfs_up(bord[x][0], x);
}

void dfs_down(int x, int par) {
	//cerr<<"dfs_down: "<<x<<" "<<par<<"\n";
	if(owner[mp(par,x)]) fadj[owner[mp(par,x)]].pb(fid);
	owner[mp(par,x)]=fid;


	if(ibord[x][par]!=sz(badj[x])-1) {
		/*for(auto i:bord[x]) {
			cerr<<i.xx<<" "<<i.yy<<"??\n";
		}
		cerr<<par<<" "<<bord[x][ibord[x][par]+1]<<" "<<ibord[x][par]<<"\n";*/
		assert(bord[x][ibord[x][par]]==par);
		dfs_up(bord[x][ibord[x][par]+1], x);
	}else {
		dfs_down(adj[x].back(), x);
	}
}

int b1[20001];

void dfs(int x, int par=-1) {
	b1[x]=1;
	//cerr<<x<<" "<<par<<"\n";
	for(int i=0;i<sz(adj[x])-1;++i) {
		origin=x;
		//cerr<<fid<<"===============\n";
		dfs_down(adj[x][i], x);
		fid++;
	}
	
	for(int i:adj[x]) {
		if(!b1[i]) dfs(i, x);
	}
	
	b1[x]=2;
}

int bb[20001];
void build(int x, int par=-1) {
	
//	cerr<<x<<" "<<par<<"\n";
	
	if(par!=-1) {
		badj[x].pb(par);
		bord[x][sz(badj[x])-1]=par;
		ibord[x][par]=sz(badj[x])-1;
		
	}
	
	if(bb[x]) return ;
	bb[x]=1;
	for(auto i:adj[x]) {
		build(i, x);
	}
	
	
	
	bb[x]=2;
}
int dp[60001];

int calc(int x) {
	
	if(dp[x]!=-1) return dp[x];
	int ans=0;
	for(auto i:fadj[x]) {
		ans=max(ans, calc(i)+1);
	}
	
	return dp[x]=ans;
}

int main() {
	IO;
	
	memset(dp, -1, sizeof dp);
	int n;
	cin>>n;
	
	for(int i=1;i<n;++i) {
		int cnt;
		cin>>cnt;
		for(int j=0;j<cnt;++j) {
			int akt;
			cin>>akt;
			adj[i].pb(akt);
			
			
			ord[i][sz(adj[i])-1]=akt;
			
			iord[i][akt]=sz(adj[i])-1;
			
			
		}
	}
	
	
	
	
	build(1);
	
	/*for(int i=1;i<=n;++i) {
	cerr<<i<<": "; for(auto j:badj[i]) {
		cerr<<j<<" ";
	}cerr<<"\n";
	}*/
	//return 0;
	
	dfs(1);
	
	/*for(int i=0;i<fid;++i) {
		cerr<<i<<": ";
		for(auto j:fadj[i]) {
			cerr<<j<<" ";
		}cerr<<"\n";
	}*/
	
	if(fid==1) {
		cout<<"1\n";
		return 0;
	}
	
	int ans=0;
	for(int i=0;i<fid;++i ){
		ans=max(ans, calc(i)+2);
	}
	
	cout<<ans<<"\n";
	
	return 0;
}

