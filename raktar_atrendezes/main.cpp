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

vector<int> adj[810];
vector<int> lst ;
vector<int> t;
vector<int> pos[400][400];
int main() {
	IO;
	int n,m;
	cin>>n>>m;
	
	lst.resize(n*m);
	for(int i=0;i<n*m;++i) {
		cin>>lst[i];
	}
	
	
	for(int i=0;i<n*m;i+=m) {
		vector<int> cnt(m+1);
		for(int j=i;j<i+m;++j) {
			cnt[lst[j]]++;
			pos[j/m][lst[j]].pb(j);
		}
		
		for(int j=1;j<=m;++j) {
		//	cerr<<cnt[j]<<" ";
			if(cnt[j]==1) continue ;
			
			if(cnt[j]==0) {
				adj[j+400].pb(i/m);
			}else {
				for(int k=0;k<cnt[j]-1;++k) {
					adj[i/m].pb(j+400);
				}
			}
		}
		//cerr<<"\n";
	}
	/*lst.push_back(-1);
	int x;
	cin>>x;
	while(x--) {
		int a,b;
		cin>>a>>b;
		swap(lst[a-1], lst[b-1]);
		for(auto i:lst) cout<<i<<" ";
		cout<<"\n";
	}*/
	
	
	
	
	stack<int> s;
	
	for(int i=0;i<n;++i) {
		if(!adj[i].empty()) {
			s.push(i);
			while(!s.empty()) {
				int tp=s.top();
				if(adj[tp].empty()) {
					t.push_back(tp);
					s.pop();
					continue ;
					}
				else {
					s.push(adj[tp].back());
					adj[tp].pop_back();
				}
			}
		}
	}
	
	
	int ans=0;
	for(int i=0;i<(int)t.size();++i) {
		if(t[i-1]<=400) ans++;
	}
	
	cout<<ans<<"\n";
	
	
	for(auto i:t) cerr<<i<<" ";
	cerr<<"\n";
	
	vector<pair<int,int>> mvs;
	int prev=0;
	for(int i=0;i<(int)t.size();++i) {
		if(i+1==(int)t.size() || (t[i]<=400 && t[i+1]<=400)) {
			int hely=n*m+1;
			
			for(int j=i;j>=prev+1;j--) {
				cerr<<t[j]<<" -> "<<t[j-1]<<"\n";
				if(t[j]<=400) {
					
				}
			}
			
			prev=i+1;
		}
	}
	
		
	return 0;
}

