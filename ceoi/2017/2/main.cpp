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

int main() {
	IO;
	int n;
	cin>>n;
	vector<double> a,b;
	for(int i=0;i<n;++i) {
		double x,y;cin>>x>>y;
		a.pb(x);
		b.pb(y);
	}
	sort(all(a));
	sort(all(b));
	reverse(all(a));
	reverse(all(b));
	
	int L=-1, R=-1;
	double s1=0,s2=0;
	double ans=0.0;
	while(L<n || R<n) {
		//cerr<<L<<" "<<R<<" "<<s1<<" "<<s2<<"\n";
		if((s1<s2 && L<n) || (R==n)) {
			s1+=a[++L]-1;
			s2-=1;
			ans=max(ans, min(s1, s2));
		}else {
			s2+=b[++R]-1;
			s1-=1;
			ans=max(ans, min(s1, s2));
		}
	}
	
	cout<<fixed<<setprecision(4)<<ans<<"\n";
	return 0;
}
