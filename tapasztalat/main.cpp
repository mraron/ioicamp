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

int n;
ll val[100001];
vector<int> adj[100001];

ll dp1[100001];
ll dp2[100001]; //max már van
ll dp3[100001]; //min már van

const ll inf=10000000000000000LL;

void dfs(int x) {
	if(sz(adj[x])==0) {
		dp1[x]=0;
		dp2[x]=val[x];
		dp3[x]=-val[x];
		return ;
	}
	
	ll szum=0;
	for(auto i:adj[x]) {
		dfs(i);
		szum+=dp1[i];
	}
	
	dp1[x]=szum;
	dp2[x]=val[x]+szum;
	dp3[x]=-val[x]+szum;
	for(auto i:adj[x]) {
		dp1[x]=max(dp1[x], szum-dp1[i]+dp2[i]-val[x]);
		dp1[x]=max(dp1[x], szum-dp1[i]+dp3[i]+val[x]);
		
		dp2[x]=max(dp2[x], szum-dp1[i]+dp2[i]);
		dp3[x]=max(dp3[x], szum-dp1[i]+dp3[i]);
	}
}

int main() {
	IO;
	cin>>n;
	for(int i=0;i<n;++i) {
		cin>>val[i+1];
	}
	for(int i=0;i<n-1;++i) {
		int a,b;
		cin>>a>>b;
		adj[a].pb(b);
	}

	dfs(1);
	cout<<dp1[1]<<"\n";
	return 0;
}

