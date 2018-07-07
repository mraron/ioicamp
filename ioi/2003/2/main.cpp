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

struct eq {
	string a,b,c;
};

const ll mod=1e9+7;
const ll p=39;

#define DIV 4
#define lastpos(x) (last[x]/DIV)
#define lastside(x) (last[x]%DIV)

unordered_map<ll, bool> hashit(vector<eq>& x, int n) {
	unordered_map<ll, bool> X;
	unordered_map<string, int> last;
	
	for(int i=0;i<n;++i) {
		last.clear();
		ll hh=0;
		for(int j=i;j<n;++j) {
			hh=(hh*p*p+lastpos(x[j].a)*p+lastside(x[j].a))%mod;
			
			last[x[j].a]=DIV*(j-i+1)+1;
			
			if(lastpos(x[j].b)<lastpos(x[j].c) || (lastpos(x[j].b)==lastpos(x[j].c) && lastside(x[j].b)<lastside(x[j].c))) {
				hh=(hh*p*p+lastpos(x[j].b)*p+lastside(x[j].b))%mod;
				last[x[j].b]=DIV*(j-i+1)+2;
				
				hh=(hh*p*p+lastpos(x[j].c)*p+lastside(x[j].c))%mod;
				last[x[j].c]=DIV*(j-i+1)+2;
			}else {
				hh=(hh*p*p+lastpos(x[j].c)*p+lastside(x[j].c))%mod;
				last[x[j].c]=DIV*(j-i+1)+2;
				
				hh=(hh*p*p+lastpos(x[j].b)*p+lastside(x[j].b))%mod;
				last[x[j].b]=DIV*(j-i+1)+2;
			}
			
			//cerr<<hh<<" "<<j-i+1<<"\n";
			X[(hh<<32)|(j-i+1)]=true;
		}
	}

	return X;
}

void hashit(vector<eq>& x, int n, unordered_map<ll, bool>& X, int& ans) {
	unordered_map<string, int> last;
	for(int i=0;i<n;++i) {
		last.clear();
		ll hh=0;
		for(int j=i;j<n;++j) {
			hh=(hh*p*p+lastpos(x[j].a)*p+lastside(x[j].a))%mod;
			last[x[j].a]=DIV*(j-i+1)+1;
			
			if(lastpos(x[j].b)<lastpos(x[j].c) || (lastpos(x[j].b)==lastpos(x[j].c) && lastside(x[j].b)<lastside(x[j].c))) {
				hh=(hh*p*p+lastpos(x[j].b)*p+lastside(x[j].b))%mod;
				last[x[j].b]=DIV*(j-i+1)+2;
				
				hh=(hh*p*p+lastpos(x[j].c)*p+lastside(x[j].c))%mod;
				last[x[j].c]=DIV*(j-i+1)+2;
			}else {
				hh=(hh*p*p+lastpos(x[j].c)*p+lastside(x[j].c))%mod;
				last[x[j].c]=DIV*(j-i+1)+2;
				
				hh=(hh*p*p+lastpos(x[j].b)*p+lastside(x[j].b))%mod;
				last[x[j].b]=DIV*(j-i+1)+2;
			}

			if(j-i+1>ans && X[(hh<<32)|(j-i+1)]) ans=max(ans, j-i+1);
		}
	}


}


int main() {
	IO;
	int n,m;
	cin>>n>>m;
	
	vector<eq> x(n), y(m);
	
	for(int i=0;i<n;++i) {
		string del;
		cin>>x[i].a>>del>>x[i].b>>del>>x[i].c;
	}
	
	for(int i=0;i<m;++i) {
		string del;
		cin>>y[i].a>>del>>y[i].b>>del>>y[i].c;
	}
	
	int ans=0;
	auto X=hashit(x, n);
	
	hashit(y, m, X, ans);

	
	cout<<ans<<"\n";
	
	return 0;
}

