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

struct el {
	int first,second;
	bool operator!=(const el& masik) const {
		return first!=masik.first || second!=masik.second;
	}
};

int n,m;
vector<int> G[100010];
int par[100010];
stack<el> v;
int dfs_cnt=0;
int dfs_low[100010], dfs_num[100010];
int st[100010];

bool ans[100010];
vector<pair<int,int>> akt;


vector<int> cadj[100010];
int st2[100010];
int color[100010];
void test() {
	int start=-1;
	for(auto i:akt) {
		start=i.xx;
		cadj[i.xx].clear();
		cadj[i.yy].clear();
		st2[i.xx]=0;
		st2[i.yy]=0;
		color[i.xx]=0;
		color[i.yy]=0;
	}
	
	for(auto i:akt)  {
		cadj[i.xx].pb(i.yy);
		cadj[i.yy].pb(i.xx);
	}
	
	queue<int> q;
	q.push(start);
	color[start]=1;
	bool paros=true;
	
	while(!q.empty()) {
		int fr=q.front();q.pop();
		
		st2[fr]=2;
		
		for(auto i:cadj[fr]) {
			if(st2[i]==0) {
				st2[i]=1;
				color[i]=2-(color[fr]-1);
				
				q.push(i);
			}else {
				if(color[i]==color[fr]) {
					paros=false;
				}
			}
		}
	}
	
	if(!paros) {
		for(auto i:akt) {
			ans[i.xx]=ans[i.yy]=true;
		}
	}
}


void dfs(int x) {
	dfs_low[x]=dfs_num[x]=++dfs_cnt;
	st[x]=1;
	
	for(auto i:G[x]) {
		if(!st[i]) {
			v.push(el{x,i});
			par[i]=x;
			dfs(i);
			
			dfs_low[x]=min(dfs_low[x], dfs_low[i]);
			if(dfs_low[i]>=dfs_num[x]) {
				if(v.top().xx==x && v.top().yy==i) {
					v.pop();
				}else {
					akt.clear();
					
					while(!v.empty() && v.top()!=el{x,i}) {
						akt.pb({v.top().xx, v.top().yy});
						
						v.pop();
					}
					if(!v.empty()) {
						akt.pb({v.top().xx, v.top().yy});
						v.pop();
					}
					
					if(!akt.empty()) test();
				}
			}
		}else if(par[x]!=i && st[i]==1) {
			dfs_low[x]=min(dfs_low[x], dfs_num[i]);
			v.push({x,i});
		}
	}
	st[x]=2;
}


int main() {
	IO;

	cin>>n>>m;
	
	for(int i=0;i<m;++i) {
		int a,b;cin>>a>>b;
		G[a].pb(b);
		G[b].pb(a);
	}
	
	for(int i=1;i<=n;++i) {
		if(!st[i]) {
			dfs(i);
			
			akt.clear();
			while(!v.empty()) {
				akt.pb({v.top().xx, v.top().yy});
				v.pop();
			}
			
			if(!akt.empty())
				test();
		}
	}
	
	
	
	
	vector<int> res;
	for(int i=1;i<=n;++i) if(ans[i]) res.pb(i);
	
	cout<<sz(res)<<"\n";
	for(auto i:res) cout<<i<<" ";
	cout<<"\n";
	return 0;
}


