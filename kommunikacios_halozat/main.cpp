
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


struct SCC {
	int n,sid;
	vector<vector<int>> adj;
	vector<vector<int>> badj;
	vector<int> ord;
	vector<int> scc, scc_sz, scc_root, b;
	
	SCC(int n_) : n(n_), sid(1), adj(n_), badj(n_), scc(n_), scc_sz(n_), scc_root(n_), b(n) {}
	
	void clear() {
		sid=0;
		for(auto& i:adj) i.clear();
		for(auto& i:badj) i.clear();
		
		ord.clear();
		scc.assign(n, 0);
		scc_sz.assign(n, 0);
		scc_root.assign(n, 0);
		b.assign(n, 0);
	}
	
	void add_edge(int x, int y) {
		adj[x].push_back(y);
		badj[y].push_back(x);
	}
	
	void dfs1(int x) {
		b[x]=1;
		for(auto i:adj[x]) {
			if(b[i]<=0) dfs1(i);
		}
		
		b[x]=2;
		ord.push_back(x);
	}
	
	void dfs2(int x, int comp) {
		b[x]=3;
		scc[x]=comp;
		scc_sz[comp]++;
		
		for(auto i:badj[x]) {
			if(b[i]<=2) dfs2(i, comp);
		}
		
		b[x]=4;
	}
	
	void do_scc() {
		for(int i=0;i<n;++i) {
			if(b[i]<=0) {
				dfs1(i);
			}
		}
		
		while(!ord.empty()) {
			int akt=ord.back();ord.pop_back();
			
			if(b[akt]<=2) {
				scc_root[sid]=akt;
				dfs2(akt, sid++);
			}
		}
	}

	vector<vector<int>> gen_sadj_linear() {
		vector<vector<int>> scc_cont(n);
		vector<vector<int>> sadj(sid);
		vector<int> last(sid, -1);
		
		for(int i=0;i<n;++i) {
			scc_cont[scc[i]].push_back(i);
		}
		
		for(int i=0;i<sid;++i) {
			for(auto j:scc_cont[i]) {
				for(auto k:adj[j]) {
					if(scc[k]==i) continue ;
					if(last[scc[k]]<i) {
						last[scc[k]]=i;
						sadj[scc[j]].push_back(scc[k]);
					}
				}
			}
		}
		
		return sadj;
	}
	
	vector<set<int>> gen_sadj_nlogn() {
		vector<set<int>> sadj(sid);
		for(int i=0;i<n;++i) {
			for(int j:adj[i]) {
				if(scc[i]!=scc[j]) {
					sadj[scc[i]].insert(scc[j]);
				}
			}
		}
		
		return sadj;
	}
};

void dfs1(int x, vector<vector<int>>& sadj, SCC& scc, vector<int>& ans) {
	ans[x]=scc.scc_sz[x];
	for(auto i:sadj[x]) {
		dfs1(i, sadj, scc, ans);
		ans[x]+=ans[i];
	}
}

vector<int> adj[100001];
int st[100001];
int cyc[100001], cycid=1;
int par[100001];

void dfs2(int x) {
	st[x]=1;
	for(auto i:adj[x]) {
		if(0==st[i]) {
			par[i]=x;
			dfs2(i);
		}else if(1==st[i]) {
			int akt=x;
			while(akt!=i) {
				cyc[akt]=cycid;
				akt=par[akt];
			}
			cyc[akt]=cycid;
			cycid++;
		}
	}
	
	st[x]=2;
}

map<pair<int,int>, int> volt;
vector<pair<int,int>> res;
void dfs3(int x) {
	st[x]=1;
	for(auto i:adj[x]) {
		if(!st[i]) {
			dfs3(i);
		}
	}
	
	int akt=par[x];
	if(akt!=-1) {
		while(par[akt]!=-1 && !volt.count(mp(par[akt], akt))) {
			if(cyc[par[akt]]==cyc[akt] && cyc[akt]>0) break; 
			volt[mp(par[akt], akt)]=true;
			akt=par[akt];
		}
		res.push_back({x, akt});
		
	}
}

int main() {
	IO;
	int n,m,r;
	cin>>n>>m>>r;
	SCC scc(n);
	
	for(int i=0;i<m;++i) {
		int a,b;
		cin>>a>>b;
		scc.add_edge(a-1,b-1);
		adj[a].push_back(b);
	}
	
	scc.do_scc();
	
	vector<vector<int>> sadj=scc.gen_sadj_linear();
	vector<int> ans(n);
	dfs1(scc.scc[r-1], sadj, scc, ans);
	
	for(int i=0;i<n;++i) {
		cout<<ans[scc.scc[i]]<<" ";
	}cout<<"\n";

	par[r]=-1;
	dfs2(r);
	for(int i=1;i<=n;++i) cerr<<i<<": "<<cyc[i]<<"\n";
	
	memset(st,0,sizeof st);
	dfs3(r);
	
	cout<<ans.size()<<"\n";
	for(auto i:res) cout<<i.xx<<" "<<i.yy<<"\n";
	return 0;
}
