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

inline bool between(int i, int j, int k) {
	if(i<=k) {
		return i<=j && j<=k;
	}
	//i>k
	return j<=k || i<=j;
}

vector<int> adj[501];

int dp0[501][501][2];
int longest[501][501];


int calc_lgst(int i, int j) {
	if(longest[i][j]!=-1) {
		return longest[i][j];
	}
	
	int ans=0;
	for(int k:adj[i]) {
		if(between(i,k,j)) {
			ans=max(ans, calc_lgst(k,j)+1);
		}
	}
	
	return longest[i][j]=ans;
}

int calc0(int i, int j, int b) {
	
	if(dp0[i][j][b]!=-1) return dp0[i][j][b];
	int ans=0;
	for(int k:adj[(b==0?i:j)]) {
		if(i==k || j==k) continue ;
		
		if(between(i,k,j)) {
			//cerr<<(b==0?i:j)+1<<" -> "<<k+1<<"\n";
			ans=max(ans, max(calc0(i,k,1), calc0(k,j,0))+1);
		}
	}
	//cerr<<i+1<<" "<<j+1<<" "<<b<<" -> "<<ans<<"\n";
	return dp0[i][j][b]=ans;
}

int dp[501];
bitset<501> calced;
int from,to,fordit;

int calc() {
	for(int k=0;k<n;++k) {
		if(between(from, k, to)) {
			
		}
	}
	
	/*
	if(calced[i]) return dp[i];
	int ans=0;
	for(auto k:adj[i]) {
		if(k==from || k==to) continue; 
		if(between((!fordit?from:to), k, (!fordit?to:from))) {
			
			if((fordit && between(i,k,from)) || (!fordit && between(from,k,i))) {
				ans=max(ans, calc(k)+1);
			}
		}else if(i!=to){
		
			if(!fordit) {
				ans=max(ans, max(calc0(to,k,1), calc0(k,from,0))+1);
			}else {
				ans=max(ans, max(calc0(k,to,0), calc0(from,k,1))+1);
			}
		}
	}
	calced[i]=1;
	return dp[i]=ans;*/
}

int main() {
	IO;
	memset(dp0, -1, sizeof dp0);
	
	int n,k;
	cin>>n>>k;
	for(int i=0;i<n;++i) {
		int akt;
		do {
			cin>>akt;
			if(akt==0) break ;
			adj[i].pb(akt-1);
	//cerr<<i+1<<" "<<akt<<"\n";
		}while(akt>0);
	}
	
	//assert(k==0);
	//cerr<<calc0(5,2,1)<<"\n";
		//return 0;
	int ans=0, ind=0;
	//cerr<<calc0(6,0,0)<<"?!?!?!!\n";
	//return 0;

	for(int i=0;i<n;++i) {
		for(auto j:adj[i]) {
			//cerr<<i+1<<","<<j+1<<" -> "<<calc0(i,j,1)<<"\n";
			if(ans<calc0(i,j,1)+1) {
				ind=i;
				ans=calc0(i,j,1)+1;
			}
			if(ans<calc0(j,i,0)+1) {
				ind=i;
				ans=calc0(j,i,0)+1;
			}
		}
	}
	
	if(k==1) {
		for(int i=0;i<n;++i) {
			for(auto j:adj[i]) {
				if(ans>=calc0(i,j,1)+calc0(j,i,0)+12) {
					continue ;
				}	
					
				
				//int i=0,j=4;
				
				calced.reset();
				
				from=i;
				to=j;
				fordit=0;
		
				if(ans<calc(to)+1) {
					ans=calc(to)+1;
			
					ind=from;
				}
				fordit=1;
				
				calced[to]=0;
				dp[to]=-1;
				
				if(ans<calc(to)+1) {
					
					//cerr<<calc0(i,j,1)+calc0(j,i,0)<<" "<<ans<<"\n";
					ans=calc(to)+1;
				
					ind=from;
				
				}
			
	
				
			}
		}
	}
	
	cout<<ans<<"\n"<<ind+1<<"\n";
	return 0;
}
