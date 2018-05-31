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

struct query {
	int x,y;
	int l,r;
	int i;
};

int n,q;
vector<int> t;
vector<vector<query>> qs;

int ans[200001];
set<int> balset[200001];
int bal[200001];
int main() {
	IO;
	cin>>n>>q;
	
	t=vector<int>(n);
	qs.resize(n);
	
	for(int i=0;i<n;++i) {
		cin>>t[i];
	}
	
	for(int i=0;i<q;++i) {
		int a,b;
		cin>>a>>b;
		
		a--;
		qs[a].pb({a,b,-1,-1, i});
		
	}
	
		
	bool rev;
	vector<int> lis, lis2;
	
	
	rev=false;
	for(int i=0;i<n;++i) {
		for(query& j:qs[i]) {
			auto it=lower_bound(all(lis), j.y);
			(!rev?j.l:j.r)=it-lis.begin();
		}
		
		
		
		auto it=lower_bound(all(lis), t[i]);
		bal[i]=it-lis.begin();
		balset[bal[i]].insert(i);
		if(it==lis.end()) {
			lis.pb(t[i]);
		}else {
			*it=t[i];
		}
	}
	
	lis2=lis;
	
	lis.clear();

	rev=true;
	for(int i=n-1;i>=0;--i) {
		for(query& j:qs[i]) {
			auto it=lower_bound(all(lis), -j.y);
			(!rev?j.l:j.r)=it-lis.begin();
		}
		
		
		
		auto it=lower_bound(all(lis), -t[i]);
		
		if(it==lis.end()) {
			lis.pb(-t[i]);
		}else {
			*it=-t[i];
		}
	}
	
	
	
	int best=lis.size();
	
	for(int i=0;i<n;++i) {
		for(auto& j:qs[i]) {
			
			if(best==j.l+j.r+1) {
				ans[j.i]=best;
			}else if(best+1==j.l+j.r+1) {
				ans[j.i]=best+1;
			}else if(best>j.l+j.r+1){
				if(sz(balset[bal[j.x]])==1) {
					ans[j.i]=best-1;
					
				}else {
					ans[j.i]=best;
					
				}
			}else assert(0);
		}
	}
	
	/*for(int i=0;i<best;++i) {
		for(auto j:balset[i]) {
			cerr<<j<<" ";
		}cerr<<"\n";
	}
	return 0;*/

	for(int i=0;i<q;++i) {
		cout<<ans[i]<<"\n";
	}
	
	return 0;
}

