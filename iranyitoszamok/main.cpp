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

const int MAXN=1000;
vector<int> pr;
int lp[MAXN];

int main() {
	IO;


	for(int i=2;i<MAXN;++i) {
		if(lp[i]==0) {
			lp[i]=i;
			pr.push_back(i);
		}
		
		for(int j=0;j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<MAXN;++j) {
			lp[i*pr[j]]=pr[j];
		}
	}
	
	
	int n;
	cin>>n;
	
	vector<vector<int>> grp;
	int akt=0;
	for(int j=0;j<4;++j) {
		vector<int> lst;
		for(int i=0;i<n/4;++i) {
			lst.push_back(akt++);
		}
		grp.push_back(lst);
	}
	
	int rem=n-4*(n/4);
	while(rem>0) {
		vector<int> lst;
		for(int i=0;i+1+n/4<=n/2 && rem>0;++i) {
			lst.push_back(akt++);
			rem--;
		}
		grp.push_back(lst);
	}
	
	/*for(auto i:grp) {
		cout<<"ez: ";for(auto j:i) cout<<j<<" ";
		cout<<"\n";
	}*/
	
	vector<int> ans(n, 1);
	int ap=0;
	for(int i=0;i<sz(grp);++i) {
		for(int j=i+1;j<sz(grp);++j)  {
			int curr=pr[ap++];
			int cnt=0;
			for(auto k:grp[i]) {
				ans[k]*=curr;
				cnt++;
			}
			for(auto k:grp[j]) {
				ans[k]*=curr;
				cnt++;
			}
			assert(cnt<=n/2);
		}
	}
	
	sort(ans.begin(), ans.end());
	for(int j=n-2;j>=0;--j) {
		ans[j]*=pr[ap++];
	}
	
	for(int i=0;i<n;++i) cout<<ans[i]<<"\n";
	
	for(int i=0;i<n;++i) {
		for(int j=i+1;j<n;++j) {
			assert(__gcd(ans[i], ans[j])>1);
		}
	}
	
	return 0;
}

