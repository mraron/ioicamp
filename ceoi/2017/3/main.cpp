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

const int N=1000001;

int n,t,m;

vector<int> adj[N];
int dp[N], dpo[N];

int par1[N], b1[N];
bool ut[N];
vector<int> lst;
void dfs1(int x) {
	if(x==t) {
		int akt=x;
		ut[m]=true;
		while(akt!=m) {
			lst.pb(akt);
			ut[akt]=true;
			akt=par1[akt];
		}
		lst.pb(m);
		reverse(all(lst));
		
		return ;
	}
	
	b1[x]=1;
	for(auto i:adj[x]) {
		if(!b1[i]) {
			par1[i]=x;
			dfs1(i);
		}
	}
	b1[x]=2;
}

int par2[N], b2[N];

void dfs_calc(int x) {
	vector<int> sub;
	
	b2[x]=1;
	for(auto i:adj[x]) {
		if(!b2[i]) {
			sub.pb(i);
			par2[i]=x;
			
			dfs_calc(i);
		}
	}
	
	b2[x]=2;

	if(sz(sub)==0) {
		dp[x]=1	;
	}else if(sz(sub)==1) {
		dp[x]=2;
	}else {
		int mx=-1, mx2=-1;
		for(auto i:sub) {
			if(dp[i]>=mx) {
				mx2=mx;
				mx=dp[i];
			}else if(dp[i]>mx2) {
				mx2=dp[i];
			}
		}
		dp[x]=sz(sub)-2+mx2+2;
	}

}
	
void dfs2(int x) {	
	if(x==t) return ;
	
	b2[x]=1;

	for(auto i:adj[x]) {
		if(b2[i]) continue ;
		par2[i]=x;
		if(!ut[i]) {
			dfs_calc(i);
		}else {
			dfs2(i);
		}
	}
	
	b2[x]=2;
} 

int main() {
	IO;
	cin>>n>>t>>m;
	
	for(int i=0;i<n-1;++i) {
		int a,b;
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	dfs1(m);
	dfs2(m);
	
	int mx=0;
	int cnt=0;
	for(int i=sz(lst)-2;i>=0;i--) {	
		
	
		for(auto j:adj[lst[i]]) {
			if(!ut[j]) cnt++;
		}

		for(auto j:adj[lst[i]]) {
			if(!ut[j]) {
				dp[j]+=cnt-1;
				mx=max(mx, dp[j]);
			}
			
		}
	}
	
	int L=0, R=3000000;
	while(L<R) {
		int mid=(L+R+1)/2;
		
		int cnt=0, cans=0;
		bool ok=true;
		for(auto j:lst) {
			if(j==t) break ;
			cnt++;
			int curr=0;
			for(auto k:adj[j]) {
				if(!ut[k] && dp[k]+cans-curr>=mid) {
					cnt--;
					cans++;
					curr++;
				}
				if(cnt<0) break;
			}
			if(cnt<0) {
				ok=false;
				break ;
			}
		}
		cerr<<L<<" "<<R<<" -> "<<ok<<"\n";
		
		if(!ok) {
			L=mid;
		}else {
			R=mid-1;
		}
	}
	
	int mid=L;
	
	cnt=0; int cans=0;
	
	for(auto j:lst) {
		if(j==t) break ;
		cnt++;
		int curr=0;
		for(auto k:adj[j]) {
			if(!ut[k] && dp[k]+cans-curr>=mid) {
				cnt--;
				cans++;
				curr++;
			}
		}
	
	}
	
	cout<<max(L,cans)<<"\n";
	return 0;
}

