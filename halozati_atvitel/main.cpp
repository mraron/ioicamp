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

struct el {
	int a,b;
	int cost,vel;
	
	bool operator<(const el& masik) const {
		return vel<masik.vel;
	}
};

vector<el> adj[4001];

int dist[4001];

int main() {
	IO;
	int n,m,c,K;
	cin>>n>>m>>c>>K;
	
	vector<el> lst(m);
	for(int i=0;i<m;++i) {
		cin>>lst[i].a>>lst[i].b>>lst[i].cost>>lst[i].vel;
	}
	
	sort(all(lst));

	for(int& i:dist) {
		i=(int)1e9;
	}
	dist[c]=0;

	vector<int> ans(n+1, -1);
	ans[c]=0;
	for(int i=m-1;i>=0;i--) {
		int j;
		for(j=i;j>=0 && lst[i].vel==lst[j].vel;j--);
		j++;
		
		for(int k=j;k<=i;++k) {
			adj[lst[k].a].pb(lst[k]);
			swap(lst[k].a, lst[k].b);
			adj[lst[k].a].pb(lst[k]);
		}
		//cerr<<j<<" "<<i<<"\n";
		priority_queue<pair<int,int>> pq;
		for(int k=j;k<=i;++k) {
			pq.push({-dist[lst[k].a], lst[k].a});
			pq.push({-dist[lst[k].b], lst[k].b});
		}
		
		while(!pq.empty()) {
			auto tp=pq.top();pq.pop();
			tp.xx=-tp.xx;
			
			if(dist[tp.yy]<tp.xx) continue ;
	
			dist[tp.yy]=tp.xx;
			
			//cerr<<tp.xx<<" "<<tp.yy<<"!!\n";cerr.flush();
			for(auto k:adj[tp.yy]) {
				if(dist[k.b]>dist[tp.yy]+k.cost) {
					if(dist[k.b]>K && dist[tp.yy]+k.cost<=K) {
						ans[k.b]=lst[i].vel;
					}
					dist[k.b]=dist[tp.yy]+k.cost;
					pq.push({-dist[tp.yy]-k.cost, k.b});
				}
			}
			
		}
		
		i=j;
	}
	
	for(int i=1;i<=n;++i) cout<<ans[i]<<"\n";
		
	
	return 0;
}
