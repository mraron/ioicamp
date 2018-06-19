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
int n,m,a,b;
vector<int> G[100001];

int dfs_cnt=0;
int dfs_low[100001], dfs_num[100001];
int bennea[100001], benneb[100001];
int par[100001];

void dfs(int x) {
	dfs_low[x]=dfs_num[x]=++dfs_cnt;
	bennea[x]|=x==a;
	benneb[x]|=x==b;
	
	for(auto i:G[x]) {
		if(!dfs_num[i]) {
			par[i]=x;
			dfs(i);
			bennea[x]|=bennea[i];
			benneb[x]|=benneb[i];
			
			dfs_low[x]=min(dfs_low[i], dfs_low[x]);
		}else if(par[x]!=i) {
			dfs_low[x]=min(dfs_num[i], dfs_low[x]);
		} 
	}
}

bool volt[100001];
int parent[100001];
bool sima(int x, int y) {
	if(y==x) {
		dfs_num[x]=-1;
		return true;
	}
	
	bool van=false;
	
	volt[x]=true;
	
	for(auto i:G[x]) {
		if(volt[i]) {
	
		}else {
			cerr<<x<<": "<<(dfs_num[x]==dfs_low[x])<<"\n";
			if(dfs_num[x]==dfs_low[x] && ((y==a && !bennea[i]) || (y==b && !benneb[i]))) continue ; 
			parent[i]=x;
			van|=sima(i,y);
		}
	}
	
	if(van) {
		dfs_num[x]=-1;
	}
	
	return van;
}

vector<bool> melyik(int src, int dis) {
	vector<bool> res(n+1), st(n+1);
	queue<int> q;
	q.push(src);
	while(!q.empty()) {
		int fr=q.front();
		q.pop();
		res[fr]=1;
		st[fr]=2;
		for(auto i:G[fr]) {
			cerr<<"wut"<<fr<<" "<<(dfs_low[fr]==dfs_num[fr])<<"\n";
			if(dfs_low[fr]==dfs_num[fr] && ((dis==a && !bennea[i]) || (dis==b && !benneb[i]))) {
				cerr<<fr<<"->"<<i<<"fr\n";
				continue ;
			}
			if(i==dis) continue ;
			if(dfs_low[i]==dfs_num[i] && ((dis==a && !bennea[i]) || (dis==b && !benneb[i]))) continue ;
			if(!st[i]) {
				q.push(i);
				st[i]=1;
			}
		}
	}
	
	return res;
}

int main() {
	cin>>n>>m>>a>>b;
	for(int i=0;i<m;++i) {
		int a,b;
		cin>>a>>b;
		
		G[a].pb(b);
		G[b].pb(a);
	}
	
	
	dfs(a);
	//sima(a,b);
	cerr<<(dfs_low[4])<<"-"<<(dfs_num[4])<<"\n";
	//return 0;
	cerr<<"bennea:";
	for(int i=1;i<=n;++i) cerr<<benneb[i]<<" ";
	cerr<<"\n";
	
	vector<bool> egyik=melyik(a,b);
	
	dfs_cnt=0;
	memset(dfs_num, 0, sizeof dfs_num);
	memset(dfs_low, 0, sizeof dfs_low);
	memset(par, 0, sizeof par);
	memset(parent, 0, sizeof parent);
	
	memset(volt, 0, sizeof volt);
	
	//dfs(b);
	//sima(b,a);
	//vector<bool> masik=melyik(b,a);
	
	
	vector<int> ans;
	
	for(int i=1;i<=n;++i) if(egyik[i] && i!=a && i!=b) ans.pb(i);
	
	cout<<sz(ans)<<"\n";
	for(auto i:ans) cout<<i<<" ";
	cout<<"\n";
	return 0;
}
