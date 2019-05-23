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

struct HunKuhn {
	vector<vector<int>> adj;
	vector<int> L,R;
	vector<int> b;
	
	HunKuhn(int n, int m): adj(n), L(n,-1), R(m,-1), b(n) {
		
	}
	
	void add_edge(int a, int b) {
		adj[a].push_back(b);
	}
	
	bool dfs(int x) {
		if(b[x]) return false;
		b[x]=true;
		for(auto i:adj[x]) {
			if(R[i]==-1 || dfs(R[i])) {
				L[x]=i;
				R[i]=x;
				return true;
			}
		}
		
		return false;
	}
	
	int match() {
		while(1) {
			bool ok=false;
			fill(b.begin(), b.end(), 0);
			for(int i=0;i<(int)L.size();++i) {
				if(L[i]==-1) {
					ok|=dfs(i);
				}
			}
			if(!ok) break ;
		}
		
		int res=0;
		for(int i=0;i<(int)L.size();++i) {
			res+=L[i]!=-1;
		}
		
		return res;
	}
	
	vector<int> vL, vR;
	void dfs2(int x) {
		if(vL[x]) return ;
		
		vL[x]=1;
		for(int i:adj[x]) {
			if(!vR[i]) {
				
				vR[i]=1;
				if(R[i]!=-1) dfs2(R[i]);
			}
		}
	}
	
	pair<vector<int>,vector<int>> minimal_vertex_cover() {
		int n=L.size(), m=R.size();

		vL.assign(n, 0);
		vR.assign(m, 0);
	
		for(int i=0;i<n;++i) {
			if(L[i]==-1) dfs2(i);
		}
		
		pair<vector<int>, vector<int>> res;
		
		for(int i=0;i<n;++i) {
			if(!vL[i]) res.xx.pb(i);
		}
		
		for(int i=0;i<m;++i) {
			if(vR[i]) res.yy.pb(i);
		}
		
		return res;
	}
};

vector<int> adj[10001];

void dfs(int x, int mely=0) {
	
}

int main() {
	IO;
	int n,m;
	cin>>n>>m;
	
	
	for(int i=0;i<m;++i) {
		int a,b;
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	
	return 0;
}
