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

int n,l;
int t[10001];

struct state {
	int k,l2;
	bool operator<(const state& masik) const {
		if(k==masik.k) return l2<masik.l2;
		return k<masik.k;
	}
};

state dp[2][10001];

int main() {
	IO;
	cin>>l>>n;
	for(int i=1;i<=n;++i) cin>>t[i];
	for(int i=0;i<=l;++i) {
		dp[0][i]={2,0};
	}
	
	for(int i=1;i<=n;++i) {
		for(int j=0;j<=l;++j) {
			dp[i&1][j]={(int)1e9,(int)1e9};
		}
		
		for(int j=0;j<=l;++j) {
			state uj=dp[(i&1)^1][j];
			uj.l2+=t[i];
			if(uj.l2>l) {
				uj.k++;
				uj.l2=t[i];
			}
			
			dp[i&1][j]=min(dp[i&1][j], uj);
		}
		
		for(int j=0;j<=l;++j) {
			if(j+t[i]<=l) {
				dp[i&1][j+t[i]]=min(dp[i&1][j+t[i]], dp[(i&1)^1][j]);
			}else {
				state uj=dp[(i&1)^1][j];
				uj.k++;
				
				dp[i&1][t[i]]=min(dp[i&1][t[i]], uj);
			}
		}
	}
	
	int ans=(int)1e9;
	for(int i=0;i<=l;++i) ans=min(ans, dp[n&1][i].k);
	cout<<ans<<"\n";
	
	return 0;
}
