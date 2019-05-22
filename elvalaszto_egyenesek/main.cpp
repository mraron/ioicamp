#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second
#define all(x) (x).begin(), (x).end()

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

bool solve(vector<pt>& ch, ll a, ll b, ll c, ll d, pt& egyik, pt& masik) {
	ll dx=c-a, dy=d-b;
	/*for(int i=0;i<(int)ch.size();++i) {
		cerr<<ccw(ch[i],{ch[i].xx+dx,ch[i].yy+dy},ch[(i+1)%sz(ch)])<<" ";
	}cerr<<" dolgok\n";
	cerr<<a<<" "<<b<<" "<<c<<" "<<d<<"\n"; */
	
	
	int X, Y, ori, akt;
	
	ori=ccw(ch[0], {ch[0].xx+dx, ch[0].yy+dy}, ch[1]);
	akt=0;
	for(int i=20;i>=0;i--) {
		int curr=akt+(1<<i);
		if(curr<sz(ch)) {
			int val=ccw(ch[curr], {ch[curr].xx+dx, ch[curr].yy+dy}, ch[(curr+1)%ch.size()]);
			if(ori==val || val==0) {
				akt=curr;
			}
		}
	} 
	X=akt;
	
	ori=ccw(ch[(X+1)%ch.size()], {ch[(X+1)%ch.size()].xx+dx, ch[(X+1)%ch.size()].yy+dy}, ch[(X+2)%ch.size()]);	
	akt=(X+1)%ch.size();
	for(int i=20;i>=0;i--) {
		int curr=akt+(1<<i);
		if(curr<sz(ch)) {
			int val=ccw(ch[curr], {ch[curr].xx+dx, ch[curr].yy+dy}, ch[(curr+1)%ch.size()]);
			if(ori==val || val==0) {
				akt=curr;
			}
		}
	} 
	Y=akt;
	
	X++;Y++;
	X%=sz(ch);Y%=sz(ch);
	
	int A=ccw({a,b},{c,d},ch[X]), B=ccw({a,b},{c,d},ch[Y]);
	/*cerr<<ch[X].ind<<" "<<ch[Y].ind<<"CHxy\n",
	cerr<<A<<" "<<B<<"\n";*/
	if(A!=B && A!=0 && B!=0) {
		egyik=ch[X];
		masik=ch[Y];
		return true;
	}
	
	return false;
}


int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,q;
	cin>>n>>q;
	vector<pt> lst(n);
	for(int i=0;i<n;++i){
		cin>>lst[i].xx>>lst[i].yy;
		lst[i].ind=i+1;
	}
	
	vector<pt> ch=hull(lst);
	/*for(auto i:ch) cerr<<i.ind<<"\n";
	cerr<<"\n";*/
	for(int i=0;i<q;++i) {
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		pt ans[2];
		if(solve(ch, a,b,c,d, ans[0], ans[1])) {
			cout<<ans[0].ind<<" "<<ans[1].ind<<"\n";
		}else {
			cout<<"0 0\n";
		}
		//cerr<<"\n";
	}
	
	
	return 0;
}
