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

int main() {
	IO;
	int n;
	cin>>n;	
	vector<int> p(n);
	for(int i=0;i<n;++i) cin>>p[i];
	
	vector<int> p2=p;
	next_permutation(all(p2));
	
	int i=0, mx=-1;
	for(;i<n && p2[i]==p[i];i++) mx=max(mx, p2[i]);
	mx=max(mx, p2[i]);
	
	vector<int> smaller, rest;
	for(int j=i+1;j<n;++j) {
		if(p2[j]<mx) smaller.pb(p2[j]);
		else rest.pb(p2[j]);
	}
	
	vector<int> ans;
	for(int j=0;j<=i;++j) ans.pb(p2[j]);
	
	sort(all(smaller));
	reverse(all(smaller));
	sort(all(rest));

	
	for(auto i:smaller) ans.pb(i);
	for(auto i:rest) ans.pb(i);
	
	for(auto i:ans) cout<<i<<" ";

	return 0;
}

