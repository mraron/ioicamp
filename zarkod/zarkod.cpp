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

int hatv[15];
int k,n;

int append(int x, int what) {
	x%=hatv[n-1];
	x*=k;
	x+=what;
	
	return x;
}

void to_str(string& buf, int x) {
	
	for(int i=n-1;i>=0;i--) {
		int cnt=0;
		while(x>=hatv[i]) {
			cnt++;
			x-=hatv[i];
		}
		
		buf.pb(cnt+'0');
	}
	
}

int last(int x) {
	return x%k;
}


bitset<2000001> volt[21];
int t[2000201];
int ind=0;
char buf[100];
int main() {

	cin>>k>>n;
	
	hatv[0]=1;
	for(int i=1;i<15;++i) {
		hatv[i]=hatv[i-1]*k;
	}
	
	
	t[ind++]=0;

	
	vector<int> tour;
	while(ind>0) {
		int akt=t[ind-1];
		
		bool done=false;
		for(int i=0;i<k;++i) {
			int nakt=append(akt, i);
			if(nakt!=akt && !volt[i][nakt]) {
				done=true; 
				t[ind++]=nakt;
				volt[i][nakt]=true;
				break ;
			}
		}
		
		if(!done) {
			tour.pb(akt);
			ind--;
		}
	}	
	
	
	tour.pop_back();
	
	
	string buf;
	buf.reserve(hatv[n-1]+100);
	to_str(buf, tour[sz(tour)-1]);
	

	for(int i=sz(tour)-2;i>=0;--i) {
		buf.pb(last(tour[i])+'0');
	}
	cout<<buf<<"\n";
	return 0;
}

