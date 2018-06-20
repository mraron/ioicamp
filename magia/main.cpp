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

int n;
string s;
map<vector<int>, int> t;

int ch[52];
char inv[255];

int main() {
	IO;
	cin>>n>>s;
	
	set<char> st;
	for(auto i:s) {
		st.insert(i);
	}
	
	
	
	int ind=0;
	for(auto i:st) {
		ch[ind]=i;
		inv[int(i)]=ind;
		ind++;
	}
	
	vector<int> nil(sz(st)-1);
	//t[nil]++;
	
	vector<int> akt(sz(st));
	ll mod=(int)1e9+7;
	ll ans=0;
	
	for(auto i:s) {
		vector<int> curr(sz(st)-1);
		
		for(int j=1;j<sz(st);++j) {
			curr[j-1]=akt[j]-akt[j-1];
		}
		
		ans+=t[curr];
		ans%=mod;
		
		t[curr]++;
		akt[inv[int(i)]]++;
	}
	
		vector<int> curr(sz(st)-1);
		
		for(int j=1;j<sz(st);++j) {
			curr[j-1]=akt[j]-akt[j-1];
		}
		
		ans+=t[curr];
		ans%=mod;
	
	
	cout<<ans<<"\n";
	return 0;
}

