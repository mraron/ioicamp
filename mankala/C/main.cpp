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
#include "game.h"
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

struct state {
	int t[4];
	int p=0;
	
	state mv(int x) {
		state uj=*this;
		uj.t[x]=0;
		uj.p=1-p;
		int eloszt=t[x]-1;
		for(int i=x+1;eloszt>0;++i) {
			if(i%4==x) continue ;
			uj.t[i%4]++;
			eloszt--;
		}
		
		return uj;
	}
	
	bool veg() {
		return (p==0 && t[0]+t[1]==0) || (p==1 && t[2]+t[3]==0);
	}
	
	bool operator==(const state& masik) const {
		return masik.t[0]==t[0] && masik.t[1]==t[1] && masik.t[2]==t[2] && masik.t[3]==t[3];
	}
	
	bool operator<(const state& masik) const {
		return t[0]<masik.t[0]||t[1]<masik.t[1]||t[2]<masik.t[2]||t[3]<masik.t[3];
	}
};

const int NY=1;
const int V=0;
map<state, pair<int,int>> dp;

pair<int,int> calc(state x) {
	if(dp.count(x)) {
		return dp[x];
	}
	
	if(x.veg()) {
		return {V,-1};
	}
	
	int Vlepes=-1;
	int lepes=-1;
	
	int L,R;
	
	if(x.p==0) L=0, R=1;
	else L=2,R=3;
	
	for(int i=L;i<=R;++i) {
		if(x.t[i]>0) {
			lepes=i;
			state y=x.mv(i);
			if(calc(y).xx==V) {
				Vlepes=i;
			}
		}
	}
	
	return dp[x]={Vlepes!=-1, (Vlepes!=-1?Vlepes:lepes)};
}


int main() {
	state X;
	X.p=0;
	for(int i=0;i<4;++i) {
		X.t[i]=Pit(i+1);
	}
	
	while(1) {
		pair<int,int> L=calc(X);
	//	cerr<<L.xx<<" "<<L.yy<<"\n";
		//assert(L.xx==NY);
		cerr<<L.yy<<"\n";
		MyMove(L.yy+1);
		X=X.mv(L.yy);
		int x=YourMove();
		X=X.mv(x-1);
	}
	
	return 0;
}

