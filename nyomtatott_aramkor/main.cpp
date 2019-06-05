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
#include<random>
#include<chrono>
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

#ifndef ONLINE_JUDGE
#  define LOG(x) (cerr << #x << " = " << (x) << endl)
#else
#  define LOG(x) ((void)0)
#endif

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const double PI=3.1415926535897932384626433832795;
const ll INF = 1LL<<62;
const ll MINF = -1LL<<62;

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

//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); uniform_int_distribution<int>(0, n-1)(rng)



struct pt {
	ll xx,yy;
	int ind;
	
	bool operator==(const pt& masik) const {
		return ind==masik.ind;
	}
	
	friend int ccw(pt, pt, pt);
	friend ll sqdist(pt, pt);
	
	bool operator<(const pt& masik) const {
		if(ccw({0,0},*this,masik)==0) return sqdist({0,0},*this)>sqdist({0,0},masik);
		return ccw({0,0},*this, masik)==1;
	}
};

ll sqdist(pt a, pt b) {
	return (a.xx-b.xx)*(a.xx-b.xx)+(a.yy-b.yy)*(a.yy-b.yy);
}

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

struct seg {
	pt xx,yy;
	
	ll val() const {
		return min(sqdist({0,0},xx), sqdist({0,0},yy));
	}
	
		
	ll valmx() const {
		return max(sqdist({0,0},xx), sqdist({0,0},yy));
	}
	
	
	bool operator<(const seg& masik) const {
		return (ccw(xx,yy,masik.xx)>0&&ccw(xx,yy,masik.yy)>0)||(ccw(masik.xx,masik.yy,xx)>0&&ccw(masik.xx,masik.yy,yy)>0);
		//return mp(xx,yy)<mp(masik.xx,masik.yy);
	}
	
	bool operator==(const seg& masik) const {
		return xx==masik.xx&&yy==masik.yy;
	}
};



struct ev {
	int typ;
	pt hely;
	seg val;
	
	bool operator<(const ev& masik) const {
		return hely<masik.hely;
	}
};




int main() {
	int n;
	cin>>n;
	vector<pt> pts(n), lst;
	for(int i=0;i<n;++i) {
		cin>>pts[i].xx>>pts[i].yy;
		pts[i].ind=i+1;
	}
	
	pt orig={0,0};
	pt from=pts[0], to=pts[0];
	for(int i=0;i<n;++i) {
		if(ccw(orig, from, pts[i])==0) {
			if(sqdist(orig,pts[i])<sqdist(orig,from)) from=pts[i];
		}else if(ccw(orig,from,pts[i])<0) {
			from=pts[i];
		}
		
		if(ccw(orig, to, pts[i])==0) {
			if(sqdist(orig,pts[i])>sqdist(orig,to)) to=pts[i];
		}else if(ccw(orig,to,pts[i])>0) {
			to=pts[i];
		}
	}

	int akt=from.ind-1;
	while(pts[akt].ind!=to.ind) {
		lst.pb(pts[akt]);
		akt--;
		if(akt<0) akt=n-1;
	}
	lst.pb(pts[akt]);
	
	/*for(auto i:lst) {
		cerr<<i.xx<<" "<<i.yy<<"\n";
	}cerr<<"\n";*/
	
	vector<ev> evs;
	for(int i=0;i+1<sz(lst);++i) {	
		seg opt={lst[i],lst[i+1]};
		
		if(opt.xx<opt.yy) {
			evs.pb(ev{1,opt.xx,opt});
			evs.pb(ev{0,opt.yy,opt});
		}else{
			evs.pb(ev{1,opt.yy,opt});
			evs.pb(ev{0,opt.xx,opt});	
		}
	}
	//cerr<<"\n";
	
	sort(evs.begin(), evs.end());
	
	for(auto i:evs) {
		cerr<<i.typ<<" "<<i.hely.ind<<"!!\n";
	}
	
	multiset<seg> active;
	set<int> ans;
	for(auto i:evs) {
		cerr<<i.typ<<" "<<i.hely.ind<<"SHALAL\n";
		for(auto i:active) {
			cerr<<i.xx.ind<<" "<<i.yy.ind<<"\n";
		}
		
		if(i.typ==1) {
			
			active.insert(i.val);
			if(*active.begin()==i.val) {
				cerr<<"<------------"<<i.hely.ind<<" 1way\n";
				for(auto i:active) {
					cerr<<i.xx.ind<<" "<<i.yy.ind<<"\n";
				}
				
				ans.insert(i.hely.ind);
			}
			
		}else {
			if(*active.begin()==i.val) {
				cerr<<"<------------"<<i.hely.ind<<" 2way\n";
				for(auto i:active) {
					cerr<<i.xx.ind<<" "<<i.yy.ind<<"\n";
				}
				
				ans.insert(i.hely.ind);
			}
	
			active.erase(active.lower_bound(i.val));
		}
		cerr<<"\n";
	}
	
	ans.insert(lst.back().ind);
	
	cout<<sz(ans)<<"\n";
	for(auto i:ans) cout<<i<<" ";
	cout<<"\n";
	return 0;
}

