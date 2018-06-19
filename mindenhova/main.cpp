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
#define gc getchar_unlocked
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

struct dset {
	vector<int> lst;
	vector<bool> van;
	int n;
	int sz=0;
	
	dset(int n_) {
		n=n_;
		van=vector<bool>(n);
	}
	
	void add(int x) {
		lst.pb(x);
		van[x]=1;
		sz++;
	}
	
	int top() {
		while(!lst.empty() && !van[lst.back()]) lst.pop_back();
		if(lst.empty()) return -1;
		return lst.back();
	}
	
	void pop() {
		int tp=top();
		if(tp==-1) return ;
		
		lst.pop_back();
		van[tp]=0;
		sz--;
	}
	
	int size() {
		return sz;
	}
	
	void del(int x) {
		van[x]=false;
		sz--;
	}
	
	bool find(int x) {
		return van[x];
	}
};

vector<int> adj[200001];
vector<int> badj[200001];

vector<int> A,B;

/*int comp[1000001];
int cid=0;
int dfs_cnt=0;
int dfs_low[1000001], dfs_num[1000001];
bool instack[1000001];
int par[1000001];
int b[1000001];
stack<int> v;

void dfs(int x) {
	b[x]=1;
	v.push(x);
	instack[x]=1;
	dfs_low[x]=dfs_num[x]=++dfs_cnt;
	//cerr<<x<<"dfs\n";
	
	for(auto i:adj[x]) {
		if(b[i]==0) {			
			//cerr<<x<<"->"<<i<<"\n";
			par[i]=x;		
			dfs(i);
			
			if(dfs_low[i]<dfs_low[x]) {
				dfs_low[x]=dfs_low[i];
			}
		}else if(instack[i]) {
			dfs_low[x]=min(dfs_low[x], dfs_num[i]);
		}
	}
	//cerr<<x<<"dfs-\n";

	b[x]=2;
	
	if(dfs_low[x]==dfs_num[x]) {
		cid++;
		//cerr<<cid<<":";
		while(!v.empty()) {
			int akt=v.top();
			instack[akt]=false;
			comp[v.top()]=cid;
			//cerr<<" "<<v.top();
			v.pop();
			
			
			if(akt==x) break;
			
		}
		
		
	}
}*/


int main() {
	IO;
	int n,m;
	n=getint<int>();
	m=getint<int>();
	
	dset incrA(n+1), incrB(n+1);
	dset remA(n+1), remB(n+1);
	
	vector<bool> voltA(n+1), voltB(n+1);

	for(int i=0;i<m;++i) {
		int a,b;
		a=getint<int>();
		b=getint<int>();
		adj[a].pb(b);
		badj[b].pb(a);

		voltA[a]=1;
		voltB[b]=1;
	}
	
	for(int i=1;i<=n;++i) {
		if(voltA[i]) A.pb(i);
		else B.pb(i);
	}
	
	int x=A[0], y=adj[A[0]][0];
	
	incrA.add(x);
	incrB.add(y);
	for(int i=1;i<sz(A);++i) {
		remA.add(A[i]);
	}
	
	for(auto i:B) {
		if(i==y) continue ;
		remB.add(i);
	}
	
	vector<pair<int,int>> ans;
	vector<pair<int,int>> parok;
	//cerr<<x<<" "<<y<<"xy\n";
	while(remA.size()>0 && remB.size()>0) {
		int akt=remA.top();
		int par=-1;
		for(auto i:adj[akt]) {
			if(remB.find(i)) {
				par=i;
				break ;
			}
		}
		
		if(par==-1) {
			int bakt=remB.top();
			int ipar=-1;
			for(auto i:badj[bakt]) {
				if(remA.find(i)) {
					ipar=i;
					break ;
				}
			}
			
			if(ipar==-1) {
				ans.pb({bakt, akt});
				
				remB.del(bakt);
				incrB.add(bakt);
				
				remA.del(akt);
				incrA.add(akt);
			}else { 
				parok.pb({ipar, bakt});
				remA.del(ipar);
				remB.del(bakt);
				
				incrA.add(ipar);
				incrB.add(bakt);
			}
		}else {
			  parok.pb({akt, par});
			  remA.del(akt);
			  remB.del(par);
			  
			  incrA.add(akt);
			  incrB.add(par);
		}
	}
	
	
	for(int i=0;i<sz(parok)-1;++i) {
		ans.pb({parok[i].yy, parok[i+1].xx});
	}
	
	ans.pb({y, parok[0].xx});
	ans.pb({parok[sz(parok)-1].yy, x});
	
	if(remA.size()==0) {
		for(auto i:B) {
			if(remB.van[i]) {
				ans.pb({i, y});
			}
		}
	}else {
		for(auto i:A) {
			if(remA.van[i]) {
				ans.pb({x, i});
			}
		}
	}
	
	
	
	cout<<sz(ans)<<"\n";
	for(auto i:ans) {
		cout<<i.xx<<" "<<i.yy<<"\n";  
	}
	
	//dfs(1);
	//cout<<cid<<"\n";
	return 0;
}

