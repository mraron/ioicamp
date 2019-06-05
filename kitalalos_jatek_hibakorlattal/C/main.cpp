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
#include "eva.h"
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
ll dp[40][150];

int main() {
	dp[0][0]=1;
	for(int h=0;h<40;++h) {
		for(int k=0;k<150;++k) {
			if(k==0) {
				dp[h][k]=1;
				continue ;
			}
			
			if(h>=1) {
				dp[h][k]=dp[h-1][k-1]*2+dp[h][k-1];
			} else {
				dp[h][k]=1;
			}
		}
	}

	/*for(int i=0;i<10;++i) {
		for(int j=0;j<10;++j) {
			cerr<<dp[i][j]<<" ";
		}cerr<<"\n";
	}*/
	
	int n=GetN();
	int h=GetH();
	
	int k;
	for(k=0;k<150;++k) {
		if(dp[h][k]>=n) break ;
	}
	//cerr<<dp[h][k]<<" "<<k<<"\n";
	/*cerr<<dp[h][k]<<"\n";
	cerr<<h<<" "<<k<<"\n";
	cerr<<dp[h][k-1]<<"\n";
	cerr<<dp[h-1][k-1]<<"\n";*/
	//	cerr<<dp[10][10]<<"AHA\n";
	int L=1,R=n;
	while(L!=R) {
		/*cerr<<h<<" "<<k<<"\n";
		cerr<<L<<" "<<R<<"LRLR\n";
		
		cerr<<kozepso<<"mid\n";
		cerr<<dp[h][k]<<" "<<R-L+1<<"ez\n";cerr.flush();
		assert(k>0);
		assert(dp[h][k]>=R-L+1);
		*/
		ll kozepso=dp[h][k-1];
		if(kozepso>=R-L+1) {
			kozepso=R-L+1;
		}
		int l=L, r=L+kozepso-1;
		while(l-L<=R-r) {
			l++;
			r++;
		}
		
		if(r>R || l-L>R-r) {
			r--;
			l--;
		}
		
		if(l==L && R==r) l++;
		
		cerr<<l<<" "<<r<<"lr\n\n";
		//cerr<<l<<" "<<r<<"\n";cerr.flush();
		int val=Kerdes(l,r);
		//cerr<<l<<" "<<r<<" -> "<<val<<"\n";cerr.flush();
		if(val==0) {
			L=l, R=r;
			k--;
		}else if(val<0) {
			R=l-1;
			k--;
			h--;
		}else {
			L=r+1;
			k--;
			h--;
		}
	}
	//cerr<<L<<"\n";
	Megoldas(L);
	
	return 0;
}

