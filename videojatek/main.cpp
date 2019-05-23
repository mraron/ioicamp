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

struct node {
	int sub[3], go[3];
	int par, link, vegz, val;
	int par_c;
	
	node() {
		memset(sub, -1, sizeof sub);
		memset(go, -1, sizeof go);
		link=-1;
	}
};

node t[333]; int ind=1;

void add(string x) {
	int akt=0;
	for(auto i:x) {
		if(t[akt].sub[i-'A']==-1) {
			t[akt].sub[i-'A']=ind++;
			t[ind-1].par=akt;
			t[ind-1].par_c=i-'A';
		}
		akt=t[akt].sub[i-'A'];
	}
	t[akt].vegz++;
}

int get_go(int x, int c); 

int get_link(int x) {
	if(t[x].link!=-1) return t[x].link;
	if(x==0 || t[x].par==0) {
		t[x].link=0;
	}else {
		t[x].link=get_go(get_link(t[x].par), t[x].par_c);
	}
	
	return t[x].link;
}

int get_go(int x, int c) {
	if(t[x].go[c]!=-1) return t[x].go[c];
	if(t[x].sub[c]!=-1) {
		t[x].go[c]=t[x].sub[c];
	}else {
		t[x].go[c]=(x==0?0:get_go(get_link(x), c));
	}
	return t[x].go[c];
}

void calc_val(int x) {
	int akt=x;
	while(akt>0) {
		t[x].val+=t[akt].vegz;
		akt=get_link(akt);
	}
}

void print(int x) {
	if(x==0) return ;
	print(t[x].par);
	cout<<char('A'+t[x].par_c);
	
}

vector<vector<int>> fr;

int dp[333][2];

int main() {
	IO;
	int n,k;
	cin>>n>>k;
	for(int i=0;i<n;++i) {
		string x;
		cin>>x;
		add(x);
	}
	
	for(int i=0;i<ind;++i) {
		calc_val(i);
		//print(i);cerr<<" ";cerr<<t[i].val<<"\n";
	}
	
	fr.resize(ind);
	
	for(int i=0;i<ind;++i) {
		for(int j=0;j<3;++j)
			fr[get_go(i,j)].push_back(i);
	}
	
	for(int x=0;x<ind;++x) dp[x][0]=-1e9;
	dp[0][0]=0;
	
	
	for(int i=1;i<=k;++i) {
		for(int j=0;j<ind;++j) {
			dp[j][i&1]=-1e9;
		}
		for(int j=0;j<ind;++j) {
			for(auto l:fr[j]) {
				dp[j][i&1]=max(dp[j][i&1], t[j].val+dp[l][(i&1)^1]);
			}
		}
	}
	
	int mx=0;
	for(int i=0;i<ind;++i) {
		mx=max(mx, dp[i][k&1]);
	}
	
	cout<<mx<<"\n";
	
	return 0;
}

