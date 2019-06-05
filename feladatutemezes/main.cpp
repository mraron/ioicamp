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

int n,m,d;
vector<pair<int,int>> lst; 
vector<int> ans[100001];

bool nemlehet(int x) {
	int day=1, akt=0;
	for(int i=0;i<sz(lst);++i) {
		//cerr<<day<<" "<<akt<<"\n";
		if(akt==x) {
			day++;
			akt=0;
		}
		
		if(lst[i].xx>day) {
			day=lst[i].xx;
			akt=0;
		}
		
		if(day-lst[i].xx>d) {
			return true;
		}
		
		akt++;
	}
	
	return day>n;
}

void construct(int x) {
	int day=1, akt=0;
	for(int i=0;i<sz(lst);++i) {
		if(akt==x) {
			day++;
			akt=0;
		}
		
		if(lst[i].xx>day) {
			day=lst[i].xx;
			akt=0;
		}
		
		assert(day<=n);
		ans[day].pb(lst[i].yy);
		
		akt++;
	}

}
	
int main() {
	IO;
	cin>>n>>d>>m;
	lst.resize(m);
	for(int i=0;i<m;++i) {
		cin>>lst[i].xx;
		lst[i].yy=i+1;
	}
	
	sort(lst.begin(), lst.end());
	
	int akt=0;
	for(int i=20;i>=0;i--) {
		int curr=akt+(1<<i);
		if(nemlehet(curr)) {
			akt=curr;
		}
	}
	
	akt++;
	cout<<akt<<"\n";
	construct(akt);
	for(int i=1;i<=n;++i) {
		for(auto j:ans[i]) {
			cout<<j<<" ";
		}cout<<"0\n";
	}
	return 0;
}
