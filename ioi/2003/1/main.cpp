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

int par[222], sz[222];
void init() {
	memset(par, -1, sizeof par);
	for(auto&i:sz) i=1;
} 

int get(int x) {
	if(par[x]==-1) return x;
	return par[x]=get(par[x]);
}

void merge(int x, int y) {
	int px=get(x), py=get(y);
	
	if(sz[px]>sz[py]) swap(px,py);

	par[px]=py;
	sz[py]+=sz[px];
}

struct edge {
	int x,y,c;
	bool operator<(const edge& masik) const {
		if(c==masik.c) {
			if(x==masik.x) {
				return y<masik.y;
			}
			
			return x<masik.x;
		}
		return c<masik.c;
	}
};

int main() {
	IO;
	int n,q;
	cin>>n>>q;
	
	set<edge> ord;
	for(int i=0;i<q;++i) {
		int a,b,c;
		cin>>a>>b>>c;
		ord.insert(edge{a,b,c});
		
		
		vector<edge> del;
		
		init();
		
		int cost=0;
		
		for(auto j:ord) {
			if(get(j.x)==get(j.y)) {
				del.pb(j);
			}else {merge(j.x, j.y); cost+=j.c;}
		}
		
		if(sz[get(1)]==n) cout<<cost<<"\n"; else cout<<"-1\n";
		
		for(auto i:del) ord.erase(i);
		
		cout.flush();
	}
	
	return 0;
}

