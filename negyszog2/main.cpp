#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second
#define all(x) (x).begin(), (x).end()

struct pt {
	ll xx, yy;
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
	
	for(int i=2;i<(int)pts.size();++i) {
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

bool benne(pt A, pt B, pt C, pt Q) {
	assert(ccw(A,B,C)>=0);
	return ccw(A,B,Q)>=0&&ccw(B,C,Q)>=0&&ccw(C,A,Q)>=0;
}


int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	int a,b;
	cin>>a>>b; a--;b--;
	
	vector<pt> t(n);
	for(int i=0;i<n;++i) {
		cin>>t[i].xx>>t[i].yy;
		t[i].ind=i+1;
	}
	
	pt A=t[a], B=t[b];
	swap(t[n-1], t[a]);
	swap(t[n-2], t[b]);
	t.pop_back(); t.pop_back();	
	n-=2;
	
	for(int i=0;i<n;++i) {
		if(ccw(A, B, t[i])==0 && sqrt(sqdist(A, t[i]))+sqrt(sqdist(B, t[i]))==sqrt(sqdist(A,B))) {
			cout<<"0 0\n";
			return 0;
		} 
	}
	
	vector<pt> felso, also;
	for(int i=0;i<n;++i) {
		if(ccw(A,B,t[i])<0) felso.pb(t[i]);
		else if(ccw(A,B,t[i])>0) also.pb(t[i]); 
	}
	
	vector<pt> fu, au;	
	
	sort(felso.begin(), felso.end(), [&](const pt& egyik, const pt& masik)->bool {
		if(ccw(A, egyik, masik)==0) {
			return sqdist(A, egyik)<sqdist(A, masik);
		}
		return ccw(A, egyik, masik)<0;
	});
		
	int last=-1;
	for(int i=0;i<(int)felso.size();++i) {
		if(last==-1 || ccw(B, felso[last], felso[i])<0) {
			fu.pb(felso[i]);
			last=i;
		}
	}
	


	sort(also.begin(), also.end(), [&](const pt& egyik, const pt& masik)->bool {
		if(ccw(B, egyik, masik)==0) {
			return sqdist(B, egyik)<sqdist(B, masik);
		}
		return ccw(B, egyik, masik)<0;
	});
		
	last=-1;
	for(int i=0;i<(int)also.size();++i) {
		if(last==-1 || ccw(A, also[last], also[i])<0) {
			au.pb(also[i]);
			last=i;
		}
	}
	
	/*cerr<<A.xx<<" "<<A.yy<<" A\n";
	cerr<<B.xx<<" "<<B.yy<<" B\n\n";
//	for(auto i:felso) cerr<<i.xx<<" "<<i.yy<<"\n";
	for(auto i:au) cerr<<i.xx<<" "<<i.yy<<"\n";*/
	int i=0, j=0;
	while(i<(int)fu.size() && j<(int)au.size()) {
		if(ccw(au[j],A,fu[i])<=0) j++;
		else if(ccw(au[j],B,fu[i])>=0) i++;
		else {
			cout<<au[j].ind<<" "<<fu[i].ind<<"\n";
			return 0;
		}
	}
	
	cout<<"0 0\n";
	return 0;
}
