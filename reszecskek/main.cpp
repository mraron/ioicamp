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
	int n,l,k;
	cin>>n>>l>>k;
	vector<pair<int,int>> x(n),y(n);
	
	for(int i=0;i<n;++i) cin>>x[i].xx>>x[i].yy;
	for(int i=0;i<n;++i) cin>>y[i].xx>>y[i].yy;
	
	vector<bool> ix(n), iy(n);
	for(int i=0;i<k;++i) {
		//cerr<<i<<"\n";
		double L=0, R=1e9;
		int it=0;
		while(it++<64) {
			//cerr<<L<<" "<<R<<"\n";
			double mid=(L+R)/2;
			double mxx=-1e13, miy=1e13;
			//vector<double> px(n), py(n);
			for(int i=0;i<n;++i) {
				if(x[i].xx>mid || ix[i]) {
					//px[i]=-1e13;
				}else {
					mxx=max(mxx, (mid-x[i].xx)*x[i].yy);
				}
			}
			
			for(int i=0;i<n;++i) {
				if(y[i].xx>mid || iy[i]) {

				}else {
					miy=min(miy, (double)l-(mid-y[i].xx)*y[i].yy);
				}
			}
			
			if(mxx<miy) {
				L=mid;
			}else {
				R=mid;
			}
		}
		
		double mxx=-1e13, miy=1e13;
		int mxind=-1, miind=-1;

		for(int i=0;i<n;++i) {
			if(!ix[i] && x[i].xx<=L) {
				double val=(L-x[i].xx)*x[i].yy;
				if(val>mxx) {
					mxx=val;
					mxind=i;
				}
			}  
		}
		
		for(int i=0;i<n;++i) {
			if(!iy[i] && y[i].xx<=L) {
				double val=l-(L-y[i].xx)*y[i].yy;
				if(val<miy) {
					miy=val;
					miind=i;
				}
	
			}  
		}
		
	
		cout<<mxind+1<<" "<<miind+1<<"\n";
		ix[mxind]=1;
		iy[miind]=1;
		
		
	}
	
	return 0;
}

