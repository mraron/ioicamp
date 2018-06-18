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
stack<int, vector<int>> v; 

int b1[20001], b2[20001], comp[20001], cid=0;
void dfs1(int x) {
	b1[x]=1;
	for(auto i:adj[x]) {
		if(!b1[i]) dfs1(i);
	}
	
	b1[x]=2;
	v.push(x);
}

void dfs2(int x, int c) {
	comp[x]=c;
	//cerr<<x<<" "<<c<<"\n";
	b2[x]=1;
	for(auto i:badj[x]) {
		
		if(!b2[i]) dfs2(i, c);
	}
	
	b2[x]=2;
}

vector<int> cadj[20001];

int b3[20001];
int indeg[20001];
bool ok=true;

void dfs3(int x) {
	b3[x]=1;
	int num=0;
	
	for(auto i:cadj[x]) {
		if(!b3[i]) {
						cerr<<x<<" "<<i<<"\n";

			num++;
			dfs3(i);
		}
	}
	
	ok&=num<=1;
	b3[x]=2;
}

int main() {
	IO;
	int T;
	cin>>T;
	while(T--) {
		int n,m;
		cin>>n>>m;
		cid=1;
		for(int i=1;i<=n;++i) {
			adj[i].clear();
			badj[i].clear();
			b1[i]=0;
			b2[i]=0;
			comp[i]=0;
		}
		
		for(int i=0;i<m;++i) {
			int a,b;
			cin>>a>>b;
			adj[a].pb(b);
			badj[b].pb(a);
		}
		
		for(int i=1;i<=n;++i) {
			if(!b1[i]) dfs1(i);
		}
		
		while(!v.empty()) {
			if(!b2[v.top()]) {
				dfs2(v.top(), cid++);
			} 
			
			v.pop();
		}
	
		for(int i=1;i<cid;++i) {
			cadj[i].clear();
			b3[i]=0;
			indeg[i]=0;
		}
		
				set<pair<int,int>> dolog;

		for(int i=1;i<=n;++i) {
			for(auto j:adj[i]) {
				if(comp[i]!=comp[j]) {
					cadj[comp[i]].pb(comp[j]);
					indeg[comp[j]]++;
					dolog.insert(mp(comp[i], comp[j]));
					
				//	cerr<<comp[i]<<" "<<comp[j]<<" cél\n";
				}
			}
		}
				for(auto i:dolog) cerr<<i.xx<<" "<<i.yy<<"\n";

		
		
		bool ans=false;
		
		for(int i=1;i<cid;++i) {
			if(indeg[i]==0) {
			//	cerr<<"VAN\n";
				ok=true;

				dfs3(i);
				
				for(int j=1;j<cid;++j) {
					ok&=b3[j]==2;
				}
				
				if(ok) ans=true;
				
				break ;
			}
		}
		
		cout<<(ans?"IGEN":"NEM")<<"\n";
		
	}
	return 0;
}

