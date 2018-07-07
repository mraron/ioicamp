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

int n,k,r;
int LL, RR;
int okcnt;
bool ok[200001];
int cnt[200001];
int need[200001];

int dna[200001];
int blksz=300;

void fit(int l, int r) {
	while(l<LL) {
		int idx=--LL;
		
		cnt[dna[idx]]++;
		if(need[dna[idx]]==cnt[dna[idx]]) {
			okcnt++;
			ok[dna[idx]]=true;
		}
	}
	
	while(RR<r) {
		int idx=++RR;
		
		cnt[dna[idx]]++;
		if(need[dna[idx]]==cnt[dna[idx]]) {
			okcnt++;
			ok[dna[idx]]=true;
		}
	}
	
	while(LL<l) {
		int idx=LL;
		
		cnt[dna[idx]]--;
		if(need[dna[idx]]-1==cnt[dna[idx]]) {
			okcnt--;
			ok[dna[idx]]=false;
		}
		
		LL++;
	}
	
	while(r<RR) {
		int idx=RR;
		
		cnt[dna[idx]]--;
		if(need[dna[idx]]-1==cnt[dna[idx]]) {
			okcnt--;
			ok[dna[idx]]=false;
		}
		
		RR--;
	}
	
	/*cerr<<LL<<" "<<RR<<" "<<okcnt<<"\n";
	cerr<<k<<": ";
	for(int i=0;i<k;++i) cerr<<cnt[i]<<" ";cerr<<"\n"; */
}

vector<pair<int,int>> blk;

int par[200001];

vector<pair<int,int>> segs;

int main() {
	IO;
	LL=0; RR=-1;
	
	cin>>n>>k>>r;
	
	memset(need, -1, sizeof need);
	
	for(int i=0;i<n;++i) {
		cin>>dna[i];
	}
	
	for(int i=0;i<r;++i) {
		int typ,c;cin>>typ>>c;
		need[typ]=max(need[typ], c);
	}
	
	for(int i=0;;++i) {
		if(blksz*i>=n) break ;
		blk.pb({i*blksz, min(n-1, blksz*(i+1)-1)});
	}
	
	int L=0, R=-1;
	
	memset(par, -1, sizeof par);
	while(L<sz(blk) && R<sz(blk)) {
		if(okcnt==r) {
			par[L]=R;
			segs.pb({blk[L].xx, blk[R].yy});
			L++;
		}else {
			R++;
		}
		
		if(L<sz(blk) && R<sz(blk)) fit(blk[L].xx, blk[R].yy);
	}
	
	int ans=1e7;
	for(int i=0;par[i]!=-1;++i) {
		for(int j=blk[i].xx;j<=blk[i].yy;++j) {
			int L=max(blk[par[i]].xx, j), R;
			if(par[i]+1<sz(blk)) R=blk[par[i]+1].yy;
			else R=blk[par[i]].yy;
			while(L<R) {
				int mid=(L+R)/2;
	
				fit(j, mid);
				
				if(okcnt==r) {
					R=mid;
				}else {
					L=mid+1;
				}
			}
			//cerr<<j<<" "<<L<<"wut\n";
		
			
			fit(j,L);
			
			if(okcnt==r){
				//cerr<<j<<" "<<L<<" "<<L-j+1<<"?\n";
			
				ans=min(ans, L-j+1);
			}
		}
	}
	
	if(ans!=1e7)
		cout<<(ans)<<"\n";
	else cout<<"impossible\n";
	return 0;
}

