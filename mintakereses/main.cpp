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
const int MAXN=500001;

struct fenwick {
	int arr[MAXN];
	
	fenwick() {memset(arr,0,sizeof arr);}
	
	void incr(int x, int by) {
		for(;x<MAXN;x+=(x&(-x))) {
			arr[x]+=by;
		}
	} 
	
	int sum(int x) {
		int sum=0;
		for(;x>0;x-=(x&(-x))) {
			sum+=arr[x];
		}
		
		return sum;
	}
};
 

int main() {
	IO;
	int n;
	cin>>n;
	vector<int> t(n), mn(n);
	for(int i=0;i<n;++i) {
		cin>>t[i];
	}
	
	mn[n-1]=t[n-1];
	for(int i=n-2;i>=0;i--) mn[i]=min(t[i], mn[i+1]);
	fenwick fw;
	for(int i=0;i+1<n;++i) {
		if(t[i]>mn[i+1] && fw.sum(t[i])-fw.sum(mn[i+1]-1)>=2) {
			vector<int> ketto;
			for(int j=0;j<i&&(int)ketto.size()<2;++j) {
				if(t[j]>=mn[i+1] && t[j]<=t[i]) {
					ketto.push_back(t[j]);
				}
			}
			ketto.push_back(t[i]);
			ketto.push_back(mn[i+1]);
			for(auto i:ketto) printf("%d ", i);
			printf("\n");
			
			return 0;
		}
		
		fw.incr(t[i], 1);
	}
	
	printf("0\n");
	
	return 0;
}
