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
#define FORN(i, n) for(int i=0;i<(n);i++)
#define gc getchar
#define IO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)

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

struct query {
	int x,y,l,r;
	int i;
};

int n,q;
vector<int> t;
vector<vector<query>> qs; 

int bal[200001], jobb[200001];
int ans[200001];
set<int> pos[200001];
int main() {
	IO;
	cin>>n>>q;
	t=vector<int>(n);
	qs=vector<vector<query>>(n);
	
	for(int i=0;i<n;++i) cin>>t[i];
	
	for(int i=0;i<q;++i) {
		int a,b;
		cin>>a>>b;
		a--;
		
		qs[a].pb({a,b,-1,-1,i});
	}
	
	vector<int> lis;
	
	for(int i=0;i<n;++i) {

		for(query& j:qs[i]) {

			auto it=lower_bound(all(lis), j.y);
			j.l=it-lis.begin();
		}
		
		
		auto it=lower_bound(all(lis), t[i]);
		bal[i]=it-lis.begin();
		
		if(it==lis.end()) {
			lis.pb(t[i]);
		}else {
			*it=t[i];
		}
		
	}
	
	lis.clear();
	
	for(int i=n-1;i>=0;--i) {
		for(query& j:qs[i]) {
			auto it=lower_bound(all(lis), -j.y);
			j.r=it-lis.begin();
		}
		
		auto it=lower_bound(all(lis), -t[i]);
		jobb[i]=it-lis.begin();
		
		if(it==lis.end()) {
			lis.pb(-t[i]);
		}else {
			*it=-t[i];
		}
	}
	
	
	int best=sz(lis);
	
	for(int i=0;i<n;++i) {
		if(bal[i]+jobb[i]+1==best) {
			pos[bal[i]].insert(i);
		}
	}
	
	for(int i=0;i<n;++i) {
		for(query& j:qs[i]) {
			if(j.l+j.r+1==best) {
				ans[j.i]=best;
			}else if(j.l+j.r==best) {
				ans[j.i]=best+1;
			}else {
				if(sz(pos[bal[i]])==1 && bal[i]+jobb[i]+1==best) {
					ans[j.i]=best-1;
				}else {
					ans[j.i]=best;
				}
			}
		}
	}
	
	for(int i=0;i<q;++i) cout<<ans[i]<<"\n";
	
	return 0;
}

