#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include "grundy.h"

using namespace std;


vector<int> dp;
vector<int> lepes;
multiset<int> akt;
void Kezd(int n){
	dp=vector<int>(n+1);
	lepes=vector<int>(n+1);
	dp[1]=0;
	dp[2]=0;
	
	for(int i=3;i<=n;++i) {
		bool nyero=false;
		for(int j=1;j<i-j&&!nyero;++j) {
			nyero|=(dp[j]^dp[i-j])^1;
		//	cerr<<j<<" "<<i-j<<" "<<nyero<<"\n";
			
			if(nyero) lepes[i]=j;
		}
		dp[i]=nyero;
	}
	
	akt.insert(n);
	
	/*for(int i=1;i<=n;++i) {
		cerr<<dp[i]<<" ";
	}cerr<<"\n";
	
	for(int i=1;i<=n;++i) {
		cerr<<lepes[i]<<" ";
	}cerr<<"\n";*/
}


void EnLepesem(int &m, int &k){
	while(!akt.empty() && *akt.begin()<=2) {
		akt.erase(akt.begin());
	}
	//cerr<<"wut\n";
	//assert(!akt.empty());
	//cerr<<*akt.begin()<<"\n";;
	//cerr<<dp[*akt.begin()]<<"dp\n";;
	//cerr<<lepes[*akt.begin()]<<"dp\n";;
	if(dp[*akt.begin()]) {
		m=lepes[*akt.begin()];
		k=*akt.begin()-lepes[*akt.begin()];
		//cerr<<m<<" "<<k<<"\n";
		akt.erase(akt.begin());
		
		akt.insert(m);
		akt.insert(k);
		
		//cerr<<m<<" "<<k<<"\n";
	}else {
		m=*akt.begin()-1;
		k=1;
		
		akt.erase(akt.begin());
		
		akt.insert(m);
		akt.insert(k);
	}
	m=m+k;
}

void TeLepesed(int m, int k){
	akt.erase(akt.lower_bound(m));
	akt.insert(m-k);
	akt.insert(k);
}

