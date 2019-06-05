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

int settcan[1001][1001];
vector<int> setscan[1001];

struct st {
	int hol=0;
	int day=0;
	int stk=0; //0->ures, 1->c-s, 2->b-s
	int a=-1,b=-1,c=-1;
};

int main() {
	IO;
	int n,k,s;
	cin>>n>>k>>s;
	for(int i=0;i<s;++i) {
		int akt;
		do {
			cin>>akt;
			if(akt==0) break; 
			settcan[i][akt]=1;
			setscan[akt].pb(i);
			//cerr<<akt<<" "<<i<<"\n";
		}while(1);
	}
	
	vector<int> lst(n);
	for(int i=0;i<n;++i) cin>>lst[i];
	
	st ans;
	
	queue<st> q;
	q.push(st{});
	
	while(!q.empty()) {
		auto fr=q.front();q.pop();
		
		/*cerr<<"hol: "<<fr.hol<<"\n";
		cerr<<"day: "<<fr.day<<"\n";
		cerr<<"stk: "<<fr.stk<<"\n";
		cerr<<fr.a<<" "<<fr.b<<" "<<fr.c<<"\n";
		cerr<<"\n";*/
		cerr<<fr.hol<<" "<<fr.day<<" "<<fr.stk<<" "<<" "<<fr.a<<" "<<fr.b<<" "<<fr.c<<"\n";
		
		if(ans.hol<fr.hol) ans=fr;
		if(ans.hol==n) break ;
		if(fr.day==3) continue ;
		
		st uj=fr;
		uj.day++;
		q.push(uj);
		
		//a
		if(fr.day==0) {
			uj=fr;
			if(fr.a==-1) {
				uj.a=0;
				for(int i:setscan[lst[fr.hol]]) {
					uj.a=i;
					uj.hol++;
					q.push(uj);
					uj.hol--;
				} 
			}else {
				if(settcan[fr.a][lst[fr.hol]]) {
					uj.hol++;
					q.push(uj);
					uj.hol--;
				}
			}
		}
		
		//b
		if((fr.day==0 && (fr.stk==2 || fr.stk==0)) || fr.day==1) {
			uj=fr;
			if(fr.b==-1) {
				uj.b=0;
				for(int i:setscan[lst[fr.hol]]) {
					uj.b=i;
					uj.hol++;
					if(fr.day==0) {
						if(fr.stk==2||fr.stk==0) {							
							int tmp=uj.stk;
							uj.stk=2;
							q.push(uj);
							uj.stk=tmp;
						}
					}else {
						q.push(uj);

					}
					uj.hol--;
				}
			}else {
				if(settcan[fr.b][lst[fr.hol]]) {
					uj.hol++;
					if(fr.day==0) {
						if(fr.stk==2||fr.stk==0) {							
							int tmp=uj.stk;
							uj.stk=2;
							q.push(uj);
							uj.stk=tmp;
						}
					}else {
						q.push(uj);

					}
					uj.hol--;
				}
			}
			
			
		
		}

		
		//c
		uj=fr;
		if(fr.c==-1) {
			uj.c=0;
			for(int i:setscan[lst[fr.hol]]) {
				uj.c=i;
				uj.hol++;
				if(fr.day==0 || fr.day==1) {
					if(fr.stk==0 || fr.stk==1) {
						int tmp=uj.stk;
						uj.stk=1;
						q.push(uj);
						uj.stk=tmp;
					}
				}else {
					q.push(uj);
				}
				uj.hol--;
			}
		}else {
			if(settcan[fr.c][lst[fr.hol]]) {
				uj.hol++;
				if(fr.day==0 || fr.day==1) {
					if(fr.stk==0 || fr.stk==1) {
						int tmp=uj.stk;
						uj.stk=1;
						q.push(uj);
						uj.stk=tmp;
					}
				}else {
					q.push(uj);
				}
				uj.hol--;
			}
		}
	
	}
	
	cout<<ans.hol<<"\n";
	vector<int> res={ans.a,ans.b,ans.c};
	if(ans.b==-1) swap(ans.b,ans.c);
	for(auto i:res) cout<<i+1<<" ";
	cout<<"\n";
	
	return 0;
}

