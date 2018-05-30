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
int adj[201][201];
int akt[201];
int ans[201];

int fokszam(int x) {
	int ans=0;
	for(int i=1;i<=n;++i) {
		if(i!=x) ans+=akt[i]&&adj[i][x];
	}
	
	return ans;
}

void solve() {
	
	
	bool ok=true;
	int odd=-1;
	for(int i=1;i<=n;++i) {
		if(akt[i]) {
			ok&=fokszam(i)%2==0;
			
			if(!ok) {
				odd=i;
				break ;
			}
			
		}
	}
	
	if(ok) {
		for(int i=1;i<=n;++i) {
			if(akt[i]) {
				ans[i]=1;
			}
		}
		
		return ;
	}
	
	vector<int> s;
	for(int i=1;i<=n;++i) {
		if(akt[i] && adj[i][odd]) s.pb(i);
		
	}
	
	for(auto i:s) {
		for(auto j:s) {
			if(i!=j) adj[i][j]=1-adj[i][j];
		}
	}
	
	akt[odd]=0;
	solve();
	akt[odd]=1;
	
	for(auto i:s) {
		for(auto j:s) {
			if(i!=j) adj[i][j]=1-adj[i][j];
		}
	}
	
	int csop[2];
	csop[0]=0;
	csop[1]=0;
	
	for(int i=1;i<=n;++i) {
		if(akt[i] && i!=odd && adj[i][odd]) {
			csop[ans[i]]++;
		}
	}
	
	if(csop[0]%2==0) {
		ans[odd]=0;
	}else {
		ans[odd]=1;
	}
}

int main() {
	IO;
	cin>>n;
	for(int i=1;i<=n;++i) {
		int cnt;
		cin>>cnt;
		for(int j=0;j<cnt;++j) {
			int akt;
			cin>>akt;
			adj[i][akt]=1;
			adj[akt][i]=1;
			
		}
	}
	
	for(int i=1;i<=n;++i) akt[i]=1;
	
	solve();
	
	vector<int> answer;
	for(int i=1;i<=n;++i) {
		if(ans[i]==0) {
			answer.pb(i);
		}
	}
	
	cout<<sz(answer)<<"\n";
	for(auto i:answer) {
		cout<<i<<" ";
	}cout<<"\n";
	return 0;
}

