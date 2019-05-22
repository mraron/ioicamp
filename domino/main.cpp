#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second

const int MAXN=100001;

int fok[MAXN];
vector<int> prt[MAXN];
vector<int> fele[MAXN];
int mn[MAXN];
int par[MAXN];
int van[MAXN];
int cmps;

int get(int x) {
	if(par[x]==-1) return x;
	return par[x]=get(par[x]);
}

void merge(int x, int y) {
	int px=get(x), py=get(y);
	if(px==py) return ;
	cmps--;
	if(sz(prt[px])>sz(prt[py])) {
		swap(px, py);
		swap(x, y);
	}
	
	par[px]=py;
	for(int i:prt[px]) {
		prt[py].pb(i);
	}
	
	prt[px].clear();
	
	mn[py]=min(mn[py], mn[px]);
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	T++;
	while(--T) {
		int n,k;
		cin>>n>>k;
		
		vector<pair<int,int>> edgs(n);
		for(int i=0;i<n;++i) {
			cin>>edgs[i].xx>>edgs[i].yy;
			fok[edgs[i].xx]=0;fok[edgs[i].yy]=0;
			prt[edgs[i].xx].clear();prt[edgs[i].yy].clear();
			par[edgs[i].xx]=-1;par[edgs[i].yy]=-1;
			
			van[edgs[i].xx]=T;
			van[edgs[i].yy]=T;
		}
		
		for(auto i:edgs) {
			fok[i.xx]++; fok[i.yy]++;
		}
		
		cmps=0;
		for(int i=1;i<=k;++i) {
			if(van[i]==T) {
				cmps++;
				if(fok[i]&1) prt[i].push_back(i);
				mn[i]=i;
			}
		}
		
		for(int i=0;i<n;++i) {
			merge(edgs[i].xx, edgs[i].yy);
		}
		
		vector<pair<int,int>> eulkr;
		
		int odd=0;
		
		for(int i=1;i<=k;++i) {
			if(van[i]==T && par[i]==-1) {
				if(prt[i].size()>0) {
					for(auto j:prt[i]) {
						odd++;
						eulkr.pb({j,1});
					}
				}else {
					eulkr.pb({mn[i],2});
				}
			} 
		}
		
		if(cmps==1 && odd<=2) {
			cout<<"0 0\n";
			continue ;
		}
		
		sort(eulkr.begin(), eulkr.end());
		
/*		for(auto i:eulkr) {
			cerr<<i.xx<<" "<<i.yy<<"\n";
		}*/
		
		int len=eulkr.size();
		
		int x=eulkr[len-1].xx, y=eulkr[len-2].xx;
		int px=get(x), py=get(y);
		
		int st=-1,en=-1;
		
		if(px!=py || prt[px].size()!=2) {//px==py csak ha prt
			st=px;
			en=py;
			eulkr[len-1].yy--;
			eulkr[len-2].yy--;
		}else {
			assert(len>=3);
			int z=eulkr[len-3].xx;
			int delta1=2*mn[px]-x-y;
			int delta2=-z-x;
			if(delta1<=delta2) {
				eulkr.push_back({mn[px], 2});
				eulkr[len-1].yy--;
				eulkr[len-2].yy--;
				st=px;
				en=px;
			}else {
				eulkr[len-3].yy--;
				eulkr[len-1].yy--;
				st=get(z);
				en=px;
			}
		}
		
		vector<pair<int,int>> ans;
		
		
		vector<int> ord;
		ord.push_back(st);
		for(int i=1;i<=k;++i) {
			if(van[i]==T && par[i]==-1) {
				fele[i].clear();
				if(st==i || en==i) continue ;
				ord.push_back(i);
			}
		}
		
		if(st!=en) ord.push_back(en);
		
		for(auto i:eulkr) {
			while(i.yy>0) {
				fele[get(i.xx)].push_back(i.xx);
				i.yy--;
			}
		}
		
		for(int i=0;i+1<sz(ord);++i) {
			ans.push_back({fele[ord[i]].back(), fele[ord[i+1]].back()});
			fele[ord[i]].pop_back(); fele[ord[i+1]].pop_back();
		}
		
		int last=-1;
		for(int i=0;i<sz(ord);++i) {
			if(last!=-1) {
				while(sz(fele[ord[last]])>0 && sz(fele[ord[i]])>0) {
					ans.push_back({fele[ord[last]].back(), fele[ord[i]].back()});
					fele[ord[last]].pop_back(); fele[ord[i]].pop_back();
				}
				
				if(sz(fele[ord[last]])==0) last=-1;
			}
			
			if(sz(fele[ord[i]])>0) {
				last=i;
			}
		}
		
		if(last!=-1) {
			assert(sz(fele[ord[last]])%2==0);
			while(sz(fele[ord[last]])>0) {
				int x=fele[ord[last]].back(); fele[ord[last]].pop_back();
				int y=fele[ord[last]].back(); fele[ord[last]].pop_back();
				ans.push_back({x,y});
			}
		}
		
		ll szum=0;
		for(auto i:ans) szum+=i.xx+i.yy;
		
		cout<<szum<<" ";
		cout<<sz(ans);
		for(auto i:ans) cout<<" "<<i.xx<<" "<<i.yy; 
		cout<<"\n";
		
		

		
		
		
		
	}
	
	return 0;
}
