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
#define gc getchar_unlocked
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

struct Node {
	int t[10];
	
	Node() {
		memset(t, 0, sizeof t);
	}
	
	Node(int x) {
		memset(t, 0, sizeof t);
		t[x]++;
	} 
	
	Node operator+(Node& masik) {
		Node ans;
		
		for(int i=0;i<10;++i) {
			ans.t[i]=t[i]+masik.t[i];
		}
		return ans;
	}
	
	void operator+=(int x) {
		int ujt[10];
			
		for(int i=0;i<10;++i) {
			ujt[(i+x)%10]=t[i];
		}
		
		for(int i=0;i<10;++i) {
			t[i]=ujt[i];
		}	
	}
	
	int sum() {
		int ans=0;
		for(int i=0;i<10;++i) {
			ans+=i*t[i];
		}
		return ans;
	}
};

struct SegTree {
	vector<int> t;
	vector<Node> tree;
	vector<int> lazy;
	
	SegTree(vector<int>& t_) {
		t=t_;
		tree.assign(4*sz(t), Node(0));
		lazy.assign(4*sz(t), 0);
	}
	
	void build() {
		build(1, 0, sz(t)-1);
	}
	
	Node query(int i, int j) {
		return query(1, 0, sz(t)-1, i, j);
	}
	
	
	
	private:
	
	inline Node combine(Node x, Node y) {
		return x+y;
	}
	
	void propogate(int ind, int L, int R) {
		if(lazy[ind]!=0) {
			if(L==R) {
				tree[ind]+=lazy[ind];
			}else {
				tree[ind]+=lazy[ind];
				
				lazy[2*ind]+=lazy[ind];
				lazy[2*ind+1]+=lazy[ind];
			}
			
			lazy[ind]=0;
		}
	}
	
	void pull(int ind, int L, int R) {
		propogate(2*ind, L, (L+R)/2);
		propogate(2*ind+1, (L+R)/2+1, R);
		tree[ind]=combine(tree[2*ind], tree[2*ind+1]);
	}
	
	void build(int ind, int L, int R) {
		if(L==R) {
			tree[ind]=Node(t[L]);
		}else {
			build(2*ind, L, (L+R)/2);
			build(2*ind+1, (L+R)/2+1, R);
			
			pull(ind, L, R);
		}
	}
	
	Node query(int ind, int L, int R, int i, int j) {
		if(R<i || j<L) return 0;
		
		propogate(ind, L, R);
		
		if(i<=L && R<=j) {
			lazy[ind]++;
			return tree[ind];
		}
		
		
		Node res=combine(query(2*ind, L, (L+R)/2, i, j), query(2*ind+1, (L+R)/2+1, R, i, j));
		pull(ind, L, R);
		
		return res;
	}
	
};

char buf[250001];
int ind;
void readStr(char buf[]) {
	char c;
	while((c=gc()) && c!=EOF && !(c>='0' && c<='9'));
	ind=0;
	do {
		buf[ind++]=c;
	}while((c=gc()) && c!=EOF && (c>='0' && c<='9'));
	
}

int main() {
	
	int n,q;
	n=getint<int>();
	q=getint<int>();
	vector<int> t(n);
	
	readStr(buf);
	for(int i=0;i<n;++i) {	
		t[i]=buf[i]-'0';
	}
	
	

	SegTree st(t);
	st.build();
	
	for(int i=0;i<q;++i) {
		int a,b;
		a=getint<int>();
		b=getint<int>();
		cout<<st.query(a-1, b-1).sum()<<"\n";
	}
	return 0;
}

