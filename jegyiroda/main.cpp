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

int main() {
	IO;
	int m,l,n;
	cin>>m>>l>>n;
	
	vector<pair<int,int>> t(n);
	vector<int> ans(n,-1);
	set<int> unused;
	for(int i=0;i<n;++i) {
		cin>>t[i].xx;
		t[i].yy=i;
		unused.insert(t[i].yy);
	}
	
	sort(t.begin(), t.end());
	
	int res=0;
	int last=0;
	vector<pair<int,int>> lst; 
	lst.pb({-100,0});
	int used=0;
	
	for(auto i:t) {
		if(i.xx>=last) {
			last=i.xx+l;
			res+=2;
			used++;
			lst.pb({i.xx, i.xx+l-1});
			ans[i.yy]=i.xx;
			unused.erase(i.yy);
		}
	}
	lst.pb({m+1,m+100});

	int poss=0;
	vector<pair<int,int>> lst2;
	for(int i=1;i<(int)lst.size();++i) {
		int val=(lst[i].xx-lst[i-1].yy-1)/l;
		poss+=val;
		lst2.push_back({lst[i-1].yy+1, val});
		
	}
	
	for(auto& i:lst2) {
		while(i.yy>0 && poss>0 && !unused.empty()) {
			res++;
			ans[*unused.begin()]=i.xx;
			unused.erase(unused.begin());
			i.xx+=l;
			i.yy--;
			poss--;
		}
	}
	
	//res+=min(poss, n-used);
	
	cout<<res<<"\n";
	int valid=0;
	for(int i=0;i<n;++i) {
		if(ans[i]>=0) valid++;
	}
	
	cout<<valid<<"\n";
	for(int i=0;i<n;++i) {
		if(ans[i]>=0) {
			cout<<i+1<<" "<<ans[i]<<"\n";
		}
	}
	return 0;
}
