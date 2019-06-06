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
#include<random>
#include<chrono>
#include<bitset>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define xx first
#define yy second
#define sz(x) (int)(x).size()
#define gc getchar
#define IO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define mp make_pair

#ifndef ONLINE_JUDGE
#  define LOG(x) (cerr << #x << " = " << (x) << endl)
#else
#  define LOG(x) ((void)0)
#endif

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const double PI=3.1415926535897932384626433832795;
const ll INF = 1LL<<62;
const ll MINF = -1LL<<62;

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

//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); uniform_int_distribution<int>(0, n-1)(rng)

const int MAXN=100001;
int n,m;
int par[2][MAXN], sz[2][MAXN];


void init() {
	for(auto& i:par[0]) i=-1;
	for(auto& i:sz[0]) i=1;
	for(auto& i:par[1]) i=-1;
	for(auto& i:sz[1]) i=1;
}

int get(int ind, int x) {
	if(par[ind][x]==-1) return x;
	return par[ind][x]=get(ind, par[ind][x]);
}

bool merge(int x, int y) {
	if(get(0,x)!=get(0,y)) {
		x=get(0,x);	y=get(0,y);
		if(sz[0][x]>sz[0][y]) swap(x,y);
		par[0][x]=y;
		sz[0][y]+=sz[0][x];
		return true;
	}else if(get(1,x)!=get(1,y)) {
		x=get(1,x);	y=get(1,y);
		if(sz[1][x]>sz[1][y]) swap(x,y);
		par[1][x]=y;
		sz[1][y]+=sz[1][x];
		return true;
	}
	
	return false;
}

vector<pair<int,int>> adj[MAXN];

int dfs_num[MAXN], dfs_low[MAXN], dfs_ind=1;
void dfs(int x, int par=-1) {
	dfs_num[x]=dfs_low[x]=dfs_ind++;
	//cerr<<x<<"!\n";
	for(auto ii:adj[x]) {
		if(ii.yy==par) continue ;
		int i=ii.xx;
		if(!dfs_num[i]) {
			dfs(i,ii.yy);
			dfs_low[x]=min(dfs_low[x], dfs_low[i]);
			if(dfs_num[x]<dfs_low[i]) {
				cout<<x<<" "<<i<<"\n";
			}
		}else {
			dfs_low[x]=min(dfs_low[x], dfs_num[i]);
		}
	}
}

int main() {
	IO;
	cin>>n>>m;
	init();
	int cnt=0;
	int idx=0;
	for(int i=0;i<m;++i) {
		int a,b;
		cin>>a>>b;
		if(merge(a,b)) {
			adj[a].pb({b,idx++});
			adj[b].pb({a,idx-1});
			cnt++;

		} 
	}

	assert(cnt<=2*(n-1));
	
	
	for(int i=1;i<=n;++i){
		if(dfs_num[i]==0) dfs(i);
	}
	
	
	return 0;
}

