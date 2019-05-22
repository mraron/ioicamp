#include<bits/stdc++.h>
using namespace std;
string t;
int n;
struct node {
	int ans;
	int ny, z;
	
	node operator+(const node& masik) const {
		node res;
		int matched=min(ny, masik.z);
		res.ans=(ans+masik.ans+matched);
		res.ny=ny+masik.ny-matched;
		res.z=z+masik.z-matched;
		return res;
	}
};

node tree[4*1000001];

void build(int ind, int L, int R) {
	if(L==R) {
		tree[ind]={0, t[L]=='(', t[L]==')'};
	}else {
		build(2*ind, L, (L+R)/2);
		build(2*ind+1, (L+R)/2+1, R);
		
		tree[ind]=tree[2*ind]+tree[2*ind+1];
	}
}

node query(int ind, int L, int R, int i, int j) {
	if(R<i || j<L) return node{0,0,0};
	if(i<=L && R<=j) {
		return tree[ind];
	}
	
	return query(2*ind, L, (L+R)/2, i, j)+query(2*ind+1, (L+R)/2+1, R, i, j);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	build(1,0,(int)t.size()-1);
	int qs;
	cin>>qs;
	for(int i=0;i<qs;++i) {
		int a,b;
		cin>>a>>b;
		cout<<2*query(1,0,(int)t.size()-1,a-1,b-1).ans<<"\n";
	}
	
	return 0;
}
