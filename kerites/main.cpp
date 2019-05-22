#include<bits/stdc++.h>
#include "lookup.h"
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second
const int maxn=100001;
int ebal[maxn], ejobb[maxn];
int prv[maxn], nxt[maxn], n;
int elozo(int x) {
	if(x==1) return n;
	return x-1;
}
int kovi(int x) {
	if(x==n) return 1;
	return x+1;
}
int main() {
	n=GetN();
	vector<int> bal, jobb;
	for(int i=1;i<=n;++i) {
		if(Drift(n+1, n+2, i)==-1) {
			jobb.pb(i);
			ejobb[i]=1;
		} else {
			bal.pb(i);
			ebal[i]=1;
		}
	}
	//for(auto i:bal) cerr<<i<<" ";cerr<<"\n";
	//for(auto i:jobb) cerr<<i<<" ";cerr<<"\n";
	for(int i=1;i<=n;++i) {
		int kov=i%n+1;
		if(ebal[i]!=ebal[kov]) {
			nxt[i]=i;
			int j;
			int elso;
			for(j=i;;j--) {
				if(j==0) j=n;
				if(ebal[i]!=ebal[j]) break ;
				elso=j;
				nxt[j]=nxt[i];
			}
			for(j=j+1;;j++) {
				if(j==n+1) j=1;
				if(ebal[i]!=ebal[j]) break; 
				prv[j]=elso;
			}
		}
	}
	
	/*for(int i=1;i<=n;++i) {
		cerr<<i<<" "<<prv[i]<<" "<<nxt[i]<<"\n";
	}*/
	
	int st=elozo(prv[1]);
	int volt=st;
	int ans1=0, ans2=0;
	do {
		int X=kovi(st);
		int Y=nxt[X];
		int jo=Y;
		//cerr<<st<<" "<<X<<" "<<Y<<"ciklus\n";
		if(X==Y) Y=kovi(Y);
		if(Drift(	st,X,Y)==-1) {
			if(ebal[X]) ans1++;
			else ans2++;
		}
		st=jo;
	}while(st!=volt);
	
	Answer(ans1, ans2);
	
	
	return 0;
}
