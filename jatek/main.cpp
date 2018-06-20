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

int main() {
	IO;
	int n,q;
	cin>>n>>q;	
	
	vector<int> t(n);
	for(int i=0;i<n;++i) cin>>t[i];
	
	vector<pair<int,int>> p(n);
	for(int i=0;i<n;++i) {
		p[i].xx=t[i];
		p[i].yy=i;
	}
	
	sort(all(p));
	
	for(int j=0;j<k;++k) {
		int akt;
		cin>>akt;
		
		queue<int> elso, masodik;
		for(int i=0;i<n;++i) {
			if(i&1) {
				masodik.push(i);
			}else {
				elso.push(i);
			}
		}
		
		
		for(int i=n-1;i>=0;i--) {
			int elerheto;
			if(p[i].yy<=akt) {
				elerheto=0;
			}else {
				elerheto=p[i].yy;
			}
		}
	}
	/*
	priority_queue<int> pq;	
	for(int i=0;i<q;++i) {
		
		int akt;
		cin>>akt;
		
		for(int j=0;j<akt;++j) {
			pq.push(t[j]);
		}
		
		int ans=0;
		int ind=0;
		while(ind<n) {
			ans+=(ind&1?-1:1)*pq.top();
			
			pq.pop();
			
			if(akt<n) {
				pq.push(t[akt]);
				akt++;
			}else {
				ind++;
				break;
			}
			
			ind++;
		}
		
		while(ind<n) {
			
			ans+=(ind&1?-1:1)*pq.top();
			
			pq.pop();
			
			ind++;
		}
		
		cout<<ans<<"\n";
	}*/
	return 0;
}
