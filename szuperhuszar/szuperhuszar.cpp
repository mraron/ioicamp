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
#define gc getchar_unlocked
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

struct par {
	ll xx, yy;
};

typedef par pt;

int ccw(pt& a, pt b, pt c) {
	b.xx-=a.xx;c.xx-=a.xx;
	b.yy-=a.yy;c.yy-=a.yy;
	
	if(b.yy*c.xx < c.yy*b.xx) {
		return -1;
	}else if(b.yy*c.xx == c.yy*b.xx) {
		return 0;
	}
	
	return 1;
}

inline double szog(pt a, pt b, pt c) {
	return a.xx*b.yy-a.yy*b.xx>0;
}

int main() {
	int T=getint<int>();

	while(T--) {
		int n=getint<int>();
		
		pt b, j;
		bool vb=false, vj=false;
		bool ve=false;
		pt orig;
		pt zero={0,0};
		
		for(int i=0;i<n;++i) {
			if(i==0) {
				orig.xx=getint<int>();
				orig.yy=getint<int>();
			} else if(i>0) {
				pt akt;
				
				akt.xx=getint<int>();
				akt.yy=getint<int>();
				
				if(ccw(zero, orig, akt)==-1 && (!vb || ccw(zero, b, akt)==-1)) b=akt, vb=true;
				else if(ccw(zero, orig, akt)==1 && (!vj || ccw(zero, j, akt)==1)) j=akt, vj=true;
				else if(ccw(zero, orig, akt)==0) {
					if(akt.xx*orig.xx<=0 && akt.yy*orig.yy<=0) {
						ve=true;
					}
				}
			}
		}
			
		ve|=vb && vj && szog(b,j,orig);
		
		bool ans=ve && vb && vj;
		ans|=ve && !vb && !vj;
		
		puts(ans?"IGEN":"NEM");
	}
	
	return 0;
}
