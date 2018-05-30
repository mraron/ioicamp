
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
#define gc getchar_unlocked
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

int main() {
	IO;
	int n,m;
	n=getint<int>();
	m=getint<int>();
	
	vector<int> t(n);
	
	for(int i=0;i<n;++i) {
		t[i]=getint<int>();
	}
	
	deque<pair<int,int>> d;
	int mx=-10000;
	for(int i=0;i<n;++i) {
		while(!d.empty() && d.back().xx>=t[i]) d.pop_back();
		d.push_back({t[i], i});
		
		if(i>=m-1) {
			while(i-d.front().yy+1>m) {
				d.pop_front();
			}
			
			mx=max(mx, d.front().xx);
		}
	}
	
	int akt=0;
	vector<int> ans;
	while(akt+m-1<n) {
		int i;
		for(i=akt+m-1;i>=akt;--i) {
			if(t[i]<=mx) break ;
		}
		
		ans.pb(i+1);
		akt=i+1;
	}
	
	cout<<sz(ans)<<"\n";
	for(auto i:ans) {
		cout<<i<<" ";
	}cout<<"\n";
	
	return 0;
}
