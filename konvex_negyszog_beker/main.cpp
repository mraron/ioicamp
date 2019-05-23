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
	bool operator==(const pt& masik) const {return ind==masik.ind;}
	pt operator+(const pt& masik) const {
		pt res={xx+masik.xx, yy+masik.yy, -1};
		return res;
	}
	pt operator*(ll x) const {
		pt res={x*xx,x*yy,-1};
		return res;
	}
	
	pt operator-(const pt& masik) const {
		pt res={xx-masik.xx, yy-masik.yy, -1};
		return res;
	}
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
	
	for(int i=2;i<sz(pts);++i) {
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


vector<pt> circular_order(vector<pt> t, pt& q) {
	vector<pt> b, j;
	j.push_back(t[0]);
	for(int i=1;i<sz(t);++i) {
		if(ccw(q, t[0], t[i])>0 || (ccw(q, t[0], t[i])==0 && t[i].xx>q.xx)) j.push_back(t[i]);
		else b.push_back(t[i]);
	}
	
	sort(j.begin(), j.end(), [&](const pt& a, const pt& b)->bool {
		return ccw(q, a, b)>0;
	});
	
	sort(b.begin(), b.end(), [&](const pt& a, const pt& b)->bool {
		return ccw(q, a, b)<0;
	});
	
	vector<pt> ord;
	for(int i=0;i<(int)j.size();++i) {
		if(i+1<(int)j.size() && ccw(q, j[i], j[i+1])==0) continue ;
		ord.push_back(j[i]);
	}
	
	for(int i=(int)b.size()-1;i>=0;i--) {
		if(i-1>=0 && ccw(q, b[i], b[i-1])==0) continue ;
		ord.push_back(b[i]);
	}
	
	return ord;
}

bool triangle_contains(pt a, pt b, pt c, pt x) {
	if(ccw(a,b,c)<0) swap(a,b);
	return ccw(a,b,x)>=0 && ccw(b,c,x)>=0 && ccw(c,a,x)>=0;
}

bool find_triangle(vector<pt>& lst, pt& q, pt& X, pt& Y, pt& Z) {
	int anti=1;
	vector<pt> ord=circular_order(lst, q);
	for(int i=0;i<(int)ord.size();++i) {
		while(int((anti+1)%ord.size())!=i && ccw(q, ord[i], ord[anti])==ccw(q, ord[i], ord[(anti+1)%ord.size()])) {
			anti++;
			anti%=ord.size();
		}
		
		if(int((anti+1)%ord.size())!=i && triangle_contains(ord[i], ord[anti], ord[(anti+1)%ord.size()], q)) {
			X=ord[i];
			Y=ord[anti];
			Z=ord[(anti+1)%ord.size()];
			//~ cerr<<"jaj"<<ord.size()<<"\n";
			for(int i=0;i<(int)lst.size();++i) {
				//~ cerr<<i<<"\n";

				if(X.ind==lst[i].ind || Y.ind==lst[i].ind || Z.ind==lst[i].ind) continue ;
				if(triangle_contains(X, Y, Z, lst[i])) {
					//~ cerr<<"itt\n";cerr.flush();
					if(triangle_contains(lst[i], Y, Z, q)) X=lst[i];
					else if(triangle_contains(X, lst[i], Z, q)) Y=lst[i];
					else if(triangle_contains(X, Y, lst[i], q)) Z=lst[i];
					else assert(0);
				}
			}
			
			
			
			return true;
		}
	}
	
	return false;
}

vector<pt> empty_triangles(pt& base1, pt& base2, vector<pt> pts) {
	vector<pt> res;
		
	sort(pts.begin(), pts.end(), [&](const pt& egyik, const pt& masik)->bool {
		if(ccw(base1, egyik, masik)==0) {
			return sqdist(base1, egyik)<sqdist(base1, masik);
		}
		return ccw(base1, egyik, masik)<0;
	});
		
	int last=-1;
	for(int i=0;i<(int)pts.size();++i) {
		if(last==-1 || ccw(base2, pts[last], pts[i])<0) {
			res.pb(pts[i]);
			last=i;
		}
	}
	
	return res;
}

bool on_segment(pt& egyik, pt& masik, pt& q) { //q equiv egyik vagy masik eset nincs kezelve
	pt irany={masik.xx-egyik.xx, masik.yy-egyik.yy};
	pt normal={-irany.yy, irany.xx};
	return ccw(egyik,masik,q)==0 && ccw(egyik, egyik+normal, q)==-ccw(masik, masik+normal, q);
}

bool empty_quadrilateral(pt& base1, pt& base2, vector<pt>& pts, pair<pt,pt>& res) {
	vector<pt> felso, also;
	for(int i=0;i<sz(pts);++i) {
		if(ccw(base1, base2, pts[i])==0 && on_segment(base1, base2, pts[i])) {
			return false;
		}
		
		if(ccw(base1, base2, pts[i])<0) felso.pb(pts[i]);
		else if(ccw(base1,base2,pts[i])>0) also.pb(pts[i]);
	}
	
	vector<pt> fu=empty_triangles(base1, base2, felso);
	vector<pt> au=empty_triangles(base2, base1, also);
	//cerr<<base1.xx<<" "<<base1.yy<<" base1\n";
	//cerr<<base2.xx<<" "<<base2.yy<<" base2\n";
	//for(auto i:fu) {
//		cerr<<i.xx<<" "<<i.yy<<" "<<i.ind<<"fu\n";
//	}
//	for(auto i:au) {
		//cerr<<i.xx<<" "<<i.yy<<" "<<i.ind<<"au\n";
	//}
	
	int i=0, j=0;
	while(i<(int)fu.size() && j<(int)au.size()) {
		if(ccw(au[j],base1,fu[i])<=0) j++;
		else if(ccw(au[j],base2,fu[i])>=0) i++;
		else {
			res.xx=au[j];
			res.yy=fu[i];
			return true;
		}
	}
	
	return false;
} 

vector<pt> szogben(vector<pt> lst, pt A, pt B, pt C) {
	if(ccw(A,B,C)>0) swap(A,C);
	vector<pt> res;
	for(auto i:lst) {
		if(ccw(B,A,i)>0 && ccw(B,C,i)<0) res.pb(i);
	}
	
	return res;
} 

vector<pt> nem_szogben(vector<pt> lst, pt A, pt B, pt C) {
	if(ccw(A,B,C)>0) swap(A,C);
	//cerr<<A.xx<<" "<<A.yy<<"A\n";
	//cerr<<B.xx<<" "<<B.yy<<"B\n";
	//cerr<<C.xx<<" "<<C.yy<<"C\n";
	vector<pt> res;
	for(auto i:lst) {
		if(ccw(B,A,i)<0 || ccw(B,C,i)>0) res.pb(i);
	}
	return res;
}

bool closest_from_right(vector<pt> lst, pt A, pt B, pt& res) {
	bool volt=false;
	for(auto i:lst) {
		if(!volt || (ccw(A, res, i)<0) || (ccw(A, res, i)==0 && sqdist(A,i)<sqdist(A,res))) {
			res=i;
			volt=true;
		}
	}
	
	return volt;
}



int main() {
	IO;
	
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		pt Q;
		//cerr<<"\n";
		scanf("%d%lld%lld", &n, &Q.xx, &Q.yy);
		
		vector<pt> t(n);
		auto answer=[&](int a, int b, int c, int d) {
			vector<int> x={b,c,d};
			sort(x.begin(), x.end(), [&](int p, int q) -> bool {
				return ccw(t[a-1],t[p-1],t[q-1])<0;
			});
			b=x[0];
			c=x[1];
			d=x[2];
			vector<pt> xd={t[a-1],t[b-1],t[c-1],t[d-1]};
			assert(hull(xd).size()==4);
		
			cout<<a<<" "<<b<<" "<<c<<" "<<d<<"\n";
			cerr<<Q.xx<<" "<<Q.yy<<"Q\n";
			cerr<<t[a-1].xx<<" "<<t[a-1].yy<<"\n";
			cerr<<t[b-1].xx<<" "<<t[b-1].yy<<"\n";
			cerr<<t[c-1].xx<<" "<<t[c-1].yy<<"\n";
			cerr<<t[d-1].xx<<" "<<t[d-1].yy<<"\n";
				bool van=false;
			for(int i=0;i<n;++i) {
				if(i+1==a || i+1==b || i+1==c || i+1==d) continue ; 
				van|=triangle_contains(t[a-1], t[b-1], t[c-1], t[i]);
				van|=triangle_contains(t[a-1], t[d-1], t[c-1], t[i]);
				if(van) {
					cerr<<t[i].xx<<" "<<t[i].yy<<" ROSZ\n";
					break ;
				}
			}
			assert(!van);
			/*assert(ccw(t[a-1], t[b-1],t[c-1])>0);
			assert(ccw(t[b-1], t[c-1],t[d-1])>0);
			assert(ccw(t[c-1], t[d-1],t[a-1])>0);
			assert(ccw(t[d-1], t[a-1],t[b-1])>0);*/
		};
		for(int i=0;i<n;++i) {
			scanf("%lld%lld", &t[i].xx, &t[i].yy);
			t[i].ind=i+1;
		}
		
		//for(auto i:t) {cerr<<i.xx<<" "<<i.yy<<"\n";}
		//~ cerr<<t.size()<<"ezkkor\n";
		//for(auto i:ord) cerr<<i.xx<<" "<<i.yy<<"\n";
		pt X,Y,Z;
		if(find_triangle(t, Q, X,Y,Z)) {
			map<int,int> val;
			if(ccw(X,Y,Z)<0) swap(Y,Z);

			val[ccw(X,Y,Q)]++;
			val[ccw(Y,Z,Q)]++;
			val[ccw(Z,X,Q)]++;
			if(val.size()==1 && val.begin()->xx!=0) {
				vector<pt> lehet1=szogben(t, Y,X,Z);
				cerr<<"van jo triangle\n";
				//~ cerr<<Q.xx<<" "<<Q.yy<<"\n";
				//~ cerr<<X.xx<<" "<<X.yy<<" X\n";
				//~ cerr<<Y.xx<<" "<<Y.yy<<" Y\n";
				//~ cerr<<Z.xx<<" "<<Z.yy<<" Z\n";
				if(!lehet1.empty()) {
					cerr<<"lehet1\n";
					pt ez;
					assert(closest_from_right(lehet1, X,Y, ez));
					answer(X.ind, Y.ind, ez.ind, Z.ind);
					//cout<<X.ind<<" "<<Y.ind<<" "<<ez.ind<<" "<<Z.ind<<"\n"; 
					goto VEGE;
				} 
				
				vector<pt> lehet2=szogben(t, Z,Y,X);
				if(!lehet2.empty()) {
					cerr<<"lehet2\n";
					pt ez;
					assert(closest_from_right(lehet2, Y,Z, ez));
					answer(Y.ind, Z.ind, ez.ind, X.ind);
					//cout<<Y.ind<<" "<<Z.ind<<" "<<ez.ind<<" "<<X.ind<<"\n"; 
					goto VEGE;
				} 
				
				
				vector<pt> lehet3=szogben(t, X,Z,Y);
				if(!lehet3.empty()) {
					cerr<<"lehet3\n";
					pt ez;
					assert(closest_from_right(lehet3, Z,X, ez));
					answer(Z.ind, X.ind, ez.ind, Y.ind);
					//cout<<Z.ind<<" "<<X.ind<<" "<<ez.ind<<" "<<Y.ind<<"\n"; 
					goto VEGE;
				} 
				
				goto NINCS;
			}else {
				//~ cerr<<"nincs jo triangle\n";
				//~ cerr<<Q.xx<<" "<<Q.yy<<"\n";
				//~ cerr<<X.xx<<" "<<X.yy<<" X\n";
				//~ cerr<<Y.xx<<" "<<Y.yy<<" Y\n";
				//~ cerr<<Z.xx<<" "<<Z.yy<<" Z\n";
				vector<pt> lst;
				for(auto i:t) {
					if(!triangle_contains(X,Y,Z,i)) {
						lst.pb(i);
					}
				}
				if(on_segment(X,Y,Q)) {
					vector<pt> jok=nem_szogben(lst, Z*2-Y, Z, Z*2-X);
					pair<pt,pt> ans;
					
					//~ cerr<<"eset1"<<jok.size()<<"\n";
					if(empty_quadrilateral(X,Y,jok, ans)) {
						answer(X.ind, ans.xx.ind, Y.ind, ans.yy.ind);
						//cout<<X.ind<<" "<<ans.xx.ind<<" "<<Y.ind<<" "<<ans.yy.ind<<"\n";
						goto VEGE;
					}
				}else if(on_segment(Y,Z,Q)) {
					vector<pt> jok=nem_szogben(lst, X*2-Y, X, X*2-Z);
					pair<pt,pt> ans;
					
					//~ cerr<<"eset2\n";
					if(empty_quadrilateral(Y,Z,jok, ans)) {
						answer(Y.ind, ans.xx.ind, Z.ind, ans.yy.ind);
						//cout<<Y.ind<<" "<<ans.xx.ind<<" "<<Z.ind<<" "<<ans.yy.ind<<"\n";
						goto VEGE;
					}
				}else if(on_segment(Z,X,Q)) {
					vector<pt> jok=nem_szogben(lst, Y*2-X, Y, Y*2-Z);
					pair<pt,pt> ans;
					
					//~ cerr<<"eset3\n";
					if(empty_quadrilateral(Z,X,jok, ans)) {
						answer(Z.ind, ans.xx.ind, X.ind, ans.yy.ind);
						//cout<<Z.ind<<" "<<ans.xx.ind<<" "<<X.ind<<" "<<ans.yy.ind<<"\n";
						goto VEGE;
					}
				}
				
				goto NINCS;
			}
		}else {
			goto NINCS;
		}
	
		NINCS: 
			cout<<"0 0 0 0\n";
			continue ;
		VEGE:
			continue ;
	}
	

	
	return 0;
}
