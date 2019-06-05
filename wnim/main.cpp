#include<bits/stdc++.h>
#include "wnim.h"
using namespace std;

const int MAXN=1e7;
int sor[MAXN];
int diff[MAXN/2+100];
int n,m;
void init() {
	memset(sor, -1, sizeof sor);
	for(int i=0,j=0;j<=MAXN;++i) {
		while(j+i<=MAXN && sor[j]!=-1) j++;
		if(j+i>MAXN) break ;
		//cerr<<j+i<<"\n";
		sor[j]=j+i;
		sor[j+i]=j;
		diff[i]=j;
		
	}
}

void Kezd(int n_, int m_) {
	init();
	n=n_;
	m=m_;
}

void EnLepesem(int &a, int &b) {
	if(sor[n]<m) {
		a=0;
		b=m-sor[n];
	}else if(sor[m]<n) {
		a=n-sor[m];
		b=0;
	}else {
		int df=abs(n-m);
		int kell;
		if(n<m) {
			kell=n-diff[df];
		}else {
			kell=m-diff[df];
		}
		
		a=kell;
		b=kell;
	}
	
	n-=a;
	m-=b;
}	

void TeLepesed(int a, int b) {
	n-=a;
	m-=b;
}
