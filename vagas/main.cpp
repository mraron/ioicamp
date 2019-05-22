#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second

struct pt {
	ll xx,yy;
	int ind;
	bool operator==(const pt& masik) const {return ind==masik.ind;}
};

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

vector<pt> hull(vector<pt> pts) {
	pt orig; bool set=false;
	
	for(auto i:pts) {
		if(!set) {
			orig=i;
			set=true;
			continue ;
		}
		
		if(orig.xx==i.xx && orig.yy>i.yy) orig=i;
		else if(orig.xx>i.xx) orig=i;
	}
	
	pts.erase(find(all(pts), orig));
	
	sort(all(pts), [orig](pt& a, pt& b) -> bool {
		if(ccw(orig,a,b)==0) return sqdist(orig,a)<sqdist(orig, b);
		return ccw(orig,a,b)>0;
	});
	
	vector<pt> hull;
	
	hull.pb(orig);
	hull.pb(pts[0]);
	hull.pb(pts[1]);
	
	for(int i=2;i<pts.size();++i) {
		hull.pb(pts[i]);
		while(hull.size()>3 && ccw(hull[hull.size()-3], hull[hull.size()-2], hull[hull.size()-1])<0) {
			pt tmp=hull.back();
			hull.pop_back();
			hull.pop_back();
			
			hull.pb(tmp);
		}
	}
	
	return hull;
}

bool metszo(pair<pt,pt> A, pair<pt,pt> B) {

}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	vector<pt> lst(n);
	for(int i=0;i<n;++i) {
		cin>>lst[i].xx>>lst[i].yy;
		lst[i].ind=i+1;
	}

	
	return 0;
}
