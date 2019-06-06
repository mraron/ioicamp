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

int n,m,A,B;
int a[MAXN], b[MAXN];

vector<pair<int,int>> adj[MAXN];
struct el {
	int a,b;
	int ind;
};

el lst[10*MAXN];


int dfs_num[MAXN], dfs_low[MAXN], dfs_ind=1;
vector<int> ans;
void dfs(int x, int par=-1) {
	dfs_num[x]=dfs_low[x]=dfs_ind++;
	//cerr<<x<<"!\n";
	for(auto ii:adj[x]) {
		if(ii.yy==par) continue ;
		int i=ii.xx;
		if(!dfs_num[i]) {
			dfs(i,ii.yy);
			a[x]+=a[i];
			b[x]+=b[i];
			dfs_low[x]=min(dfs_low[x], dfs_low[i]);
			if(dfs_num[x]<dfs_low[i] && (a[i]==A || a[i]==0 || b[i]==B || b[i]==0)) {
				ans.pb(ii.yy);
			}
		}else {
			dfs_low[x]=min(dfs_low[x], dfs_num[i]);
		}
	}
}
int main() {
	IO;
	cin>>n>>m>>A>>B;
	for(int i=0;i<A;++i) {
		int x;
		cin>>x;
		a[x]=1;
	}
	
	for(int i=0;i<B;++i) {
		int x;
		cin>>x;
		b[x]=1;
	}
	
	for(int i=0;i<m;++i) {
		int a,b;
		cin>>a>>b;
		lst[i]={a,b,i};
		adj[a].pb({b,i});
		adj[b].pb({a,i});
	}
	
	for(int i=1;i<=n;++i) {
		if(dfs_num[i]==0) {
			dfs(1,-1);
		}
	}
	
	cout<<sz(ans)<<"\n";
	for(auto i:ans) {
		cout<<lst[i].a<<" "<<lst[i].b<<"\n";
	}
	
	return 0;
}
