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

const int MAXN=10001;

int n,m;
int st[MAXN], par[MAXN];

vector<int> adj[MAXN];
vector<int> adj2[MAXN];
vector<int> A, B;
bool isA[MAXN];

bool dfs(int x) {
	if(x<=0) return false;
	if(st[x]) return false;
	
	st[x]=1;
	
	for(auto i:adj[x]) {
		if(par[i]<=0 || dfs(par[i])) {
			par[i]=x;
			par[x]=i;
			return true;
		}
	}
	
	return false;
}

void dfs(int x, int t) {
	st[x]=1;
	if(t==0) {
		isA[x]=true;
		A.pb(x);
	}
	else B.pb(x);
	
	for(auto i:adj[x]) {
		if(!st[i]) {
			dfs(i, 1-t);
		}
	}
	st[x]=2;
}

void dfs2(int x) {
	st[x]=1;
	for(auto i:adj2[x]) {
		if(!st[i]) {
			dfs2(i);
		}
	}
}

int main() {
	cin>>n>>m;
	for(int i=0;i<m;++i) {
		int a,b;
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	for(int i=1;i<=n;++i) {
		if(!st[i]) {
			dfs(i, 0);
		}
	}
	
	while(1) {
		bool volt=false;
		fill(st,st+n+1,0);
		for(auto i:A){
			if(!st[i] && par[i]==0) {
				volt|=dfs(i);
			}
		}
		if(!volt) break;
	}
	
	for(auto i:A) {
		for(auto j:adj[i]) {
			if(par[i]==j) {
				adj2[j].pb(i);
			}else {
				adj2[i].pb(j);
			}
		}
	}
	
	fill(st,st+n+1,0);
	
	for(int i=1;i<=n;++i)  {
		if(isA[i] && par[i]==0 && !st[i]) {
			dfs2(i);
		}
	}
	
	vector<int> A1, A2, A3;
	vector<int> B1, B2, B3;
	for(int i=1;i<=n;++i) {
		if(isA[i]) {
			if(par[i]==0) {
				A1.pb(i);
			}else if(st[i]) {
				A2.pb(i);
			}else {
				A3.pb(i);
			}
		}else {
			if(par[i]==0) {
				B1.pb(i);
			}else if(st[i]) {
				B2.pb(i);
			}else {
				B3.pb(i);
			}
		}
	}
	
	vector<int> ans;
	for(auto i:A1) ans.pb(i);
	for(auto i:A2) ans.pb(i);
	for(auto i:B3) ans.pb(i);
	for(auto i:B1) ans.pb(i);
	
	cout<<sz(ans)<<"\n";
	for(auto i:ans) {
		cout<<i<<" ";
	}cout<<"\n";
	
	return 0;
}
