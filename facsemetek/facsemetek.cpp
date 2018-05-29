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

struct pont {
	int xx,yy,i;
};

typedef pont pt;

int ccw(pt a, pt b, pt c) {
	b.xx-=a.xx;c.xx-=a.xx;
	b.yy-=a.yy;c.yy-=a.yy;
	
	if(b.yy*c.xx < c.yy*b.xx) {
		return -1;
	}else if(b.yy*c.xx == c.yy*b.xx) {
		return 0;
	}
	
	return 1;
}

ll sqdist(pt a, pt b) {
	return (a.xx-b.xx)*(a.xx-b.xx)+(a.yy-b.yy)*(a.yy-b.yy);
}

bool benne(vector<pt> poly, pt p) {
	if(ccw(poly[0], poly[1], poly[2])>0) swap(poly[1], poly[2]);
	
	bool ok=true;
	vector<int> lista;
	for(int i=0;i<sz(poly);++i) {
		int j=(i+1)%sz(poly);
		lista.pb(ccw(poly[i], poly[j], p));
	}
	
	for(int i=1;i<sz(lista);++i) {
		ok&=lista[i]==lista[i-1];
	}
	
	return ok;
}

pt uj, kiv;

void coolprint(pt x, pt y, pt z) {
	assert(benne({x,y,z}, uj));

	if(ccw(x, y, z)==-1) cout<<y.i<<" "<<z.i<<"\n";
	else cout<<z.i<<" "<<y.i<<"\n";
}

int main() {
	IO;
	int n,id;
	
	cin>>n>>id>>uj.xx>>uj.yy;

	vector<pt> t(n+1);
	for(int i=1;i<=n;++i) {
		cin>>t[i].xx>>t[i].yy;
		t[i].i=i;
	}
	
	kiv=t[id];
	t.erase(t.begin()+id);
	
	bool van=false;
	pt idd; 
	
	for(int i=1;i<=n;++i) {
		if(i==id) continue ;
		if(ccw(uj, kiv, t[i])==0 && ( (!van && sqdist(kiv, uj)<sqdist(kiv, t[i]) ) || ( van && sqdist(kiv, t[i]) < sqdist(kiv, idd) ) )  )  {
			van=true;
			idd=t[i];
		}
	}
	

	vector<pt> up, down;
	for(int j=1;j<n;++j) {
		pt i=t[j];
		//cerr<<i.xx<<" "<<i.yy<<"\n"; 
		if(ccw(kiv,uj, i)==-1) up.pb(i);
		else if(ccw(kiv, uj, i)==1) down.pb(i);
	}
	//return 0;
	
	auto cmp=[&](pt& a, pt& b) -> bool {
		if(ccw(kiv,a,b)==0) {
			return sqdist(kiv,a)<sqdist(kiv, b);
		}
		
		return ccw(kiv, a, b)>0;
	};
	
	sort(all(up), cmp);
	sort(all(down), cmp);
	
	
	if(!van) {
		if(up.empty() || down.empty()) {
			cout<<"0 0\n";
		}else {
			if(benne({kiv, up.back(), down[0]}, uj)) {
				coolprint(kiv, up.back(), down[0]);
			}else cout<<"0 0\n";
			//cout<<up.back().i<<" "<<down[0].i<<"\n";
		}
	}else {
		vector<pt> ujup, ujdown;
		
		
		for(int i=sz(up)-1;i>=0;i--) {
			int j=i;
			while(i>=0 && ccw(kiv, up[j], up[i])==0) i--;
			i++;
			
			if(ujup.empty() || ccw(up[i], ujup.back(), idd)==1) {
				ujup.pb(up[i]);
			}
		}
		
		for(int i=0;i<sz(down);++i) {
			
			
			if(ujdown.empty() || ccw(down[i], ujdown.back(), idd)==-1) {
				ujdown.pb(down[i]);
			}
			
			int j=i;
			while(i<sz(down) && ccw(kiv, down[j], down[i])==0) i++;
			i--;
		}
		
		/*
		for(auto i:ujup) cerr<<i.xx<<" "<<i.yy<<"\n";
		cerr<<"===============\n";
		for(auto i:ujdown) cerr<<i.xx<<" "<<i.yy<<"\n";
		*/
		int L=0, R=sz(ujdown)-1;
		
		while(L<sz(ujup) && R>=0) {
			if(benne({kiv, ujup[L], ujdown[R]}, uj) && !benne({kiv, ujup[L], ujdown[R]}, idd)) {
				coolprint(kiv, ujup[L], ujdown[R]);
				return 0;
			}
			
			if(!benne({ujup[L], ujdown[R], kiv}, uj)) R--;
			else L++;
		}
		
		cout<<"0 0\n";
	}
	
	
	return 0;
}
