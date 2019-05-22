#include<bits/stdc++.h>
#include "muszer.h"
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second
#define mp make_pair

const int MAXN=10001;
int volt[MAXN];
int n;
set<int> st;

map<pair<int,int>, int> cache;
int q(int x, int y) {
	if(cache.count(mp(x,y))!=0) return cache[mp(x,y)];
	return cache[mp(x,y)]=Kozte(x,y);
}

bool szomszedos(int x, int y) {
	return q(x,y)==x || q(x,y)==y;
}

void init(list<int>& lst) {
	int uj=*st.begin();
	st.erase(uj);
	
	list<int> mo={uj};
	volt[uj]=true;
	while(!szomszedos(*mo.begin(), *lst.rbegin())) {
		int val=q(*mo.begin(), *lst.rbegin());
		//cerr<<*mo.begin()<<" | "<<val<<" | "<<*lst.rbegin()<<"\n";
		volt[val]=true;
		st.erase(val);
		
		if(szomszedos(val,*lst.rbegin())) lst.insert(lst.end(), val);
		else mo.insert(mo.begin(), val);
	}
	//for(auto i:lst) cerr<<i<<" "; cerr<<"\n";
	//for(auto i:mo) cerr<<i<<" "; cerr<<"\n";
	
	lst.splice(lst.end(), mo);
}

void extend(list<int>& lst) {
	int uj=*st.begin();
	st.erase(uj);
	
	list<int> mo={uj};
	volt[uj]=true;
	
	int elso;
	do {
		elso=q(*next(lst.begin()), *mo.begin());
		//cerr<<*next(lst.begin())<<"\n";
		//cerr<<uj<<"EZAZUJ\n";
		//cerr<<elso<<"WAT\n";
		if(volt[elso]) {
			if(elso==*lst.begin()) {
				lst.reverse();
				break ;
			}else {
				//ez igy jo
				break ;
			}
		}else { //2 darabból áll @TODO
			#define LOG(x) cerr<<(#x)<<" = "<<(x)<<"\n";
			if(lst.size()==2) {
				if(szomszedos(elso, *mo.begin())) {
					mo.insert(mo.begin(), elso);
					st.erase(elso);
					volt[elso]=true;
				}else {
					lst.insert(lst.end(), elso);
					st.erase(elso);
					volt[elso]=true;
				}
			}else {
				mo.insert(mo.begin(), elso);
				st.erase(elso);
				volt[elso]=true;
			}
			
			/*if(lst.size()==2) {
				LOG("egyik");
				while(!szomszedos(*lst.rbegin(), elso)) {
					mo.insert(mo.begin(), elso);
					st.erase(elso);
					volt[elso]=true;
					elso=q(*next(lst.begin()), *mo.begin());
				}
				
				lst.insert(lst.end(), elso);
				st.erase(elso);
				volt[elso]=true;
			}else {
				LOG("masik");
				while(!szomszedos(*next(lst.begin()), elso)) {
					mo.insert(mo.begin(), elso);
					st.erase(elso);
					volt[elso]=true;
					elso=q(*next(lst.begin()), *mo.begin());
				}
			}*/
		}
	}while(1);
	while(!szomszedos(*mo.begin(), *lst.rbegin())) {
		int val=q(*mo.begin(), *lst.rbegin());
		volt[val]=true;
		
		st.erase(val);
		
		if(szomszedos(val,*lst.rbegin())) lst.insert(lst.end(), val);
		else mo.insert(mo.begin(), val);
	}
	
	//for(auto i:mo) cerr<<i<<" ";cerr<<"EZEGYMÁSIKOLDAL\n";
	
	lst.splice(lst.end(), mo);
}	


int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=Atomszam();
	for(int i=1;i<=n;++i) {
		st.insert(i);
	}
		
	list<int> sol={1};
	st.erase(1);
	volt[1]=true;
	init(sol);
	
	//for(auto i:sol) {
		//cerr<<i<<" ";
	//}
	//cerr<<"\n";
	
	while(!st.empty()) {
		extend(sol);
	}
	
	//for(auto i:sol) {
		//cerr<<i<<" ";
	//}
	//cerr<<"\n";
	
	int ind=1;
	for(int i:sol) {
		Sorrend(ind++, i);
	}
	
	return 0;
}

