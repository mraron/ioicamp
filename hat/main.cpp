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

vector<ll> divs;
vector<ll> divmask;
vector<ll> primes;

ll cnt[1<<6];

ll dp[14][1<<6][1<<6];

ll calc(int len, int mask1, int mask2) {
	cerr<<len<<" "<<mask1<<" "<<mask2<<"\n";
	if(dp[len][mask1][mask2]!=-1) return dp[len][mask1][mask2];
	
	ll ans=len>0;
	for(int i=1;i<(1<<sz(primes));++i) {
		if((mask2&i)>0) continue ;
		ans+=cnt[i]*calc(len+1, mask1|i, mask2|(mask1&i));
		ans%=1000000007;
	}
	cerr<<len<<" "<<mask1<<" "<<mask2<<" -> "<<ans<<"\n";
	return dp[len][mask1][mask2]=ans;
}

int main() {
	IO;
	ll n;
	cin>>n;
	for(ll i=1;i<=sqrt(n);++i) {
		if(n%i==0) {
			divs.pb(i);
			divs.pb(n/i);
		}
	}
	
	sort(all(divs));
	auto it=unique(all(divs));
	divs.resize(distance(divs.begin(),it));
	
	for(int i=1;i<sz(divs);++i) {
		bool no=true;
		for(ll j:primes) {
			if(__gcd(divs[i], j)>1) no=false;
			if(!no) break ;
		}
		
		if(no) primes.pb(divs[i]);
	}
	
	for(auto i:primes) cerr<<i<<" ";
	cerr<<"primes\n";
	for(int i=1;i<sz(divs);++i) {
		int mask=0;
		for(int j=0;j<sz(primes);++j) {
			if(divs[i]%primes[j]==0) {
				mask|=1<<j;
			}
		}
		divmask.pb(mask);
		cnt[mask]++;
		cerr<<mask<<" "<<divs[i]<<"\n";
	}
	
	for(int i=0;i<(1<<sz(primes));++i) {
		cerr<<cnt[i]<<"cnt\n";
	}
	
	memset(dp, -1, sizeof dp);
	
	cout<<calc(2,3,0)<<"\n";
	
	return 0;
}

