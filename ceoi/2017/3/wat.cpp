#include <algorithm>  

#include <iostream>  

#include <sstream>  

#include <string>  

#include <cstring>

#include <vector>  

#include <queue>  

#include <set>  

#include <map>  

#include <cstdio>  

#include <cstdlib>  

#include <cctype>  

#include <cmath>  

#include <list>  

#include <cassert>

#include <ctime>

#include <climits>

using namespace std;  



#define PB push_back  

#define MP make_pair  

#define SZ(v) ((int)(v).size())  

#define FOR(i,a,b) for(int i=(a);i<(b);++i)  

#define REP(i,n) FOR(i,0,n)  

#define FORE(i,a,b) for(int i=(a);i<=(b);++i)  

#define REPE(i,n) FORE(i,0,n)  

#define FORSZ(i,a,v) FOR(i,a,SZ(v))  

#define REPSZ(i,v) REP(i,SZ(v))  

typedef long long ll;

typedef unsigned long long ull;

ll gcd(ll a,ll b) { return b==0?a:gcd(b,a%b); }



const int MAXN=1000000;

const int MAXM=MAXN-1;



int n,t,s;

int ghead[MAXN],gnxt[2*MAXM],gto[2*MAXM],deg[MAXN];



int p[MAXN],np;

int eat[MAXM],ecost[MAXM],ne;





bool findpath(int at,int par) {

    if(at==t) { np=0; p[np++]=at; return true; }

    for(int x=ghead[at];x!=-1;x=gnxt[x]) {

	int to=gto[x]; if(to==par) continue;

	if(findpath(to,at)) { p[np++]=at; return true; }

    }

    return false;

}



int calccost(int at,int par) {

    if(deg[at]==1) return 1;

    if(deg[at]==2) return 2;

    int mx=0,mx2=0;

    for(int x=ghead[at];x!=-1;x=gnxt[x]) {

	int to=gto[x]; if(to==par) continue;

	int cur=calccost(to,at);

	if(cur>mx) mx2=mx,mx=cur; else if(cur>mx2) mx2=cur;

    }

    return mx2+deg[at]-1;

}



bool ok(int limcost) {

    int haveblock=0;

    for(int le=0,re=le;le<ne;le=re) {

	while(re<ne&&eat[le]==eat[re]) ++re;

	int curblock=0;

	FOR(i,le,re) {

	    int curcost=haveblock+ecost[i]+(ne-le-1);

	    if(curcost>limcost) ++curblock;

	}

	int canblock=min(limcost,eat[le]+1);

	if(haveblock+curblock>canblock) return false;

	haveblock+=curblock;

    }

    return true;

}





int solve() {

    assert(findpath(s,-1)); reverse(p,p+np);

    //printf("p:"); REP(i,np) printf(" %d",p[i]+1); puts("");



    ne=0;

    REP(i,np-1) {

	int at=p[i];

	for(int x=ghead[at];x!=-1;x=gnxt[x]) {

	    int to=gto[x]; if(i!=0&&to==p[i-1]||to==p[i+1]) continue;

	    eat[ne]=i; ecost[ne]=calccost(to,at); ++ne;

	}

    }

    //printf("e:"); REP(i,ne) printf(" %d=%d",eat[i],ecost[i]); puts("");



    int l=-1,h=n-1;

    while(l+1<h) {

	int m=l+(h-l)/2;

	if(ok(m)) h=m; else l=m;

    }

    return h;

}



void run() {

    scanf("%d%d%d",&n,&t,&s); --t,--s;

    REP(i,n) ghead[i]=-1,deg[i]=0;

    REP(i,n-1) {

	int a,b; scanf("%d%d",&a,&b); --a,--b;

	gnxt[2*i+0]=ghead[a],ghead[a]=2*i+0,gto[2*i+0]=b,++deg[a];

	gnxt[2*i+1]=ghead[b],ghead[b]=2*i+1,gto[2*i+1]=a,++deg[b];

    }

    printf("%d\n",solve());

}



int main() {

    run();

    return 0;

}


