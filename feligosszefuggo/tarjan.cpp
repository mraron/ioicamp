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

vector<int> adj[20001];
int par[20001], dfs_low[20001], dfs_num[20001], b[20001], comp[20001];
int instack[20001];
stack< int, vector<int> > v;
int cid=0, dfs_cnt=0;
vector<int> cadj[20001];
vector<int> elemei[20001];

int b3[20001];
int indeg[20001];
bool ok=true;

void dfs3(int x) {
	b3[x]=1;
	int num=0;
	//cerr<<x<<"DFS3\n";
	for(auto i:cadj[x]) {
		if(!b3[i]) {
		//	cerr<<x<<" "<<i<<"\n";
			num++;
			dfs3(i);
		}
	}
		//cerr<<x<<"DFS3-\n";

	b3[x]=2;
}
int last=-1;

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
			elemei[cid].pb(v.top());
			v.pop();
			
			
			if(akt==x) break;
			
		}
		
		
	}
}

int main() {
	IO;
	int T;
	cin>>T;
	
	while(T--) {

		int n,m;
		cin>>n>>m;
		
		cid=0;
		dfs_cnt=0;
		while(!v.empty()) v.pop();
		for(int i=0;i<=n;++i) {
			cadj[i].clear();
			adj[i].clear();
			elemei[i].clear();
			b[i]=0;
			comp[i]=0;
			dfs_low[i]=0;
			dfs_num[i]=0;
			instack[i]=0;
			b3[i]=0;
			indeg[i]=0;
			par[i]=0;
		}
		
		for(int i=0;i<m;++i) {
			int a,b;
			cin>>a>>b;
		
			adj[a].pb(b);
		}
		
		
		
		for(int i=1;i<=n;++i) {
			if(b[i]==0) {
			//	cerr<<"START ON "<<i<<"\n";
				dfs(i);
				assert(v.empty());
			}
		}
		
		
		//cerr<<cid<<"CID \n";
		//for(int i=1;i<=n;++i) cerr<<comp[i]<<" ";
		//cerr<<"\n";
		
		set<pair<int,int>> dolog;
		
		
		vector<int> van(cid+1);
		
		for(int i=1;i<=cid;++i) {
			for(auto j:elemei[i]) {
				for(auto k:adj[j]) {
					if(van[comp[k]]<i && comp[k]!=i) {
						van[comp[k]]=i;
						cadj[i].pb(comp[k]);
						indeg[comp[k]]++;
						//dolog.insert(mp(i, comp[k]));
					}
				}
			}
		}
		


/*		for(int i=1;i<=n;++i) {
			for(auto j:adj[i]) {
				if(comp[i]!=comp[j]) {
					cadj[comp[i]].pb(comp[j]);
					indeg[comp[j]]++;
					dolog.insert(mp(comp[i], comp[j]));
					
					//cerr<<comp[i]<<" "<<comp[j]<<" cél\n";
				}
			}
		}*/
		//cerr<<sz(dolog)<<"?\n";
		//for(auto i:dolog) cerr<<i.xx<<" "<<i.yy<<"\n";

		
		bool ans=false;
		

		for(int i=1;i<=cid;++i) sort(all(cadj[i]));
		
		for(int i=1;i<=cid;++i) {
			if(indeg[i]==0) {
			//	cerr<<i<<"VAN?!?!\n";
				ok=true;

				dfs3(i);
				
				for(int j=1;j<=cid;++j) {
					
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

