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

vector<pair<int,int>> adj[95111];

int main() {
	IO;
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;++i) {
		int a,b;
		char c;
		cin>>a>>b>>c;
		
		adj[a].pb({b, c=='F'});
		adj[b].pb({a, c=='F'});
	}
	
	int s,e;
	cin>>s>>e;
	
	deque<int> q;
	q.push_back(s);
	
	vector<int> par(n+1, -1), dist(n+1), b(n+1);
	
	while(!q.empty()) {
		int fr=q.front();
		q.pop_front();
		
		if(b[fr]) continue ;
		b[fr]=1;
		
		for(auto j:adj[fr]) {
			if(j.yy && !b[j.xx] && (par[j.xx]==-1 || dist[j.xx]>dist[fr]+1)) {
				q.push_back(j.xx);
				dist[j.xx]=dist[fr]+1;
				par[j.xx]=fr;
			}else if(!j.yy && !b[j.xx] && (par[j.xx]==-1 || dist[j.xx]>dist[fr])) {
				q.push_front(j.xx);
				dist[j.xx]=dist[fr];
				par[j.xx]=fr;
			}
		}
	}
	
	int akt=e;
	vector<int> ans;
	
	while(par[akt]!=-1) {
		ans.pb(akt);
		akt=par[akt];
	}
	
	reverse(all(ans));
	cout<<dist[e]<<"\n"<<s;
	for(auto i:ans) {
		cout<<" "<<i;
	}cout<<"\n";
	
	return 0;
}
