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

const int UNUSED=13;
const int USEDTWICE=12;
unordered_map<ll, int> dp[14];
//int dp[14][14][14][14][14][14][14];

int calc(int i, int a, int b, int c, int d, int e, int f) {
	ll id=ll(a)*100*100*100*100*100+ll(b)*100*100*100*100+c*100*100*100+d*100*100+e*100+f;
	
	if(dp[i].find(id)!=dp[i].end()) return dp[i][id];
	
	int volt[6];
	volt[0]=a;
	volt[1]=b;
	volt[2]=c;
	volt[3]=d;
	volt[4]=e;
	volt[5]=f;
	
	ll ans=1;

	for(int j=1;j<(1<<sz(primes));++j) {
		int uj[6];
		//for(auto& k:uj) k=UNUSED;
		
		bool ok=true;
		int dolog[15];
		int diff=0;

		for(auto& k:dolog) k=0;
		for(int k=0;k<sz(primes)&&ok;++k) {
			if((j&(1<<k))!=0) {
				if(volt[k]==USEDTWICE) ok=false;
				if(volt[k]!=UNUSED) {
					
					dolog[volt[k]]++;
					if(dolog[volt[k]]==1) diff++;
					
					ok&=diff<2;
				}
				
				if(volt[k]==UNUSED) uj[k]=i;
				else uj[k]=USEDTWICE;
				
			
				
			}else {
				uj[k]=volt[k];
			}
		}
		
		if(!ok) continue ;
		else {
			ans+=cnt[j]*calc(i+1, uj[0], uj[1], uj[2], uj[3], uj[4], uj[5]);
			ans%=1000000007;
		}
	}
	
	return dp[i][id]=ans;
		
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
	
	
	for(int i=1;i<sz(divs);++i) {
		int mask=0;
		for(int j=0;j<sz(primes);++j) {
			if(divs[i]%primes[j]==0) {
				mask|=1<<j;
			}
		}
		divmask.pb(mask);
		cnt[mask]++;
		
	}
	
	
	cout<<calc(0, UNUSED, UNUSED, UNUSED, UNUSED, UNUSED, UNUSED)-1<<"\n";
	
	return 0;
}

