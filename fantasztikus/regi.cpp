#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second

struct node {
	int mn,mncnt;
};

node combine(const node& egyik, const node& masik) {
	if(egyik.mn==masik.mn) {
		return {egyik.mn, egyik.mncnt+masik.mncnt};
	}
	
	if(egyik.mn<masik.mn) return egyik;
	return masik;
}

const int MAXP=100001;
const int MAXN=100001;

int n,k,m;

int arr[MAXN];
int lazy[4*MAXN];
node tree[4*MAXN];

void build(int ind, int L, int R) {
	if(L==R) {
		lazy[ind]=0;
		tree[ind]={0,1};
	}else {
		lazy[ind]=0;
		build(2*ind, L, (L+R)/2);
		build(2*ind+1, (L+R)/2+1, R);
		tree[ind]=combine(tree[2*ind], tree[2*ind+1]);
	}
}

void apply(int ind, int L, int R) {
	if(lazy[ind]!=0) {
		tree[ind].mn+=lazy[ind];
		if(L!=R) {
			lazy[2*ind]+=lazy[ind];
			lazy[2*ind+1]+=lazy[ind];
		}
		
		lazy[ind]=0;
	}
}

void upd(int ind, int L, int R, int i, int j, int by) {
	apply(ind, L, R);
	if(R<i || j<L) return ;
	if(i<=L && R<=j) {
		lazy[ind]+=by;
		apply(ind, L, R);
		return ;
	}
	
	upd(2*ind, L, (L+R)/2, i, j, by);
	upd(2*ind+1, (L+R)/2+1, R, i, j, by);
	
	tree[ind]=combine(tree[2*ind], tree[2*ind+1]);
}

void upd(int l, int r, int by) {
	if(l>r) return ;
	l=max(l,0);
	//cerr<<l<<" "<<r<<"UPD\n";
	upd(1, 0, n-k, l, r, by);
}

int pr[MAXP];

set<int> pos[MAXP];

void add_ind(int p, int ind) {
//	cerr<<p<<" "<<ind<<"\n";
	auto it=pos[p].insert(ind).xx;
	
	int prv_ind=(it==pos[p].begin()?-1:*prev(it));
	int nxt_ind=(next(it)==pos[p].end()?-1:*next(it));
	//cerr<<prv_ind<<" "<<nxt_ind<<"\n";
	if(prv_ind!=-1 && nxt_ind!=-1) {
		//cerr<<"közötte\n";
		upd(nxt_ind-k+1,prv_ind, -1);
	}
	
	if(prv_ind!=-1) {
		//cerr<<"előtte"<<prv_ind<<" "<<ind<<"\n";
		upd( ind-k+1, prv_ind, 1);
	}
	
	if(nxt_ind!=-1) {
	//	cerr<<"utána\n";
		upd(nxt_ind-k+1, ind , 1);
	}
}

void rem_ind(int p, int ind) {
	auto it=pos[p].lower_bound(ind);

	int prv_ind=(it==pos[p].begin()?-1:*prev(it));
	int nxt_ind=(next(it)==pos[p].end()?-1:*next(it));
	
	if(prv_ind!=-1 && nxt_ind!=-1) {
		upd( nxt_ind-k+1, prv_ind, 1);
	}
	
	if(prv_ind!=-1) {
		upd(ind-k+1, prv_ind, -1);
	}
	
	if(nxt_ind!=-1) {
		upd(nxt_ind-k+1, ind, -1);
	}
	
	pos[p].erase(it);
}

int curr_ans() {
	if(tree[1].mn!=0) return n-k+1;
	return n-k+1-tree[1].mncnt;
}


#define gc getchar_unlocked
int getint() {
	char c;
	int res=0;
	while((c=gc()) && !(c>='0' && c<='9'));
	do {
		res=(res*10)+c-'0';
		//cerr<<c<<"KARAKTER\n";
	}while((c=gc()) && (c>='0' && c<='9'));
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	pr[1]=0;
	for(int i=2;i<=ceil(sqrt(MAXP));++i) {
		if(!pr[i]) {
			pr[i]=i;
			for(int j=i*i;j<MAXP;j+=i) {
				pr[j]=i;
			}
		}
	}
	for(int i=2;i<MAXP;++i) {
		if(pr[i]==0) pr[i]=i;
	}
	
	
	
	int T=getint();
	while(T--) {
		for(int i=0;i<MAXP;++i) pos[i].clear();
		n=getint();
		k=getint();
		m=getint();
		build(1, 0, n-k);
		for(int i=0;i<n;++i) {
			arr[i]=getint();
			int akt=arr[i];
			while(akt>1) {
				int curr=pr[akt];
				//cerr<<akt<<" "<<curr<<"WUT\n";
				while(akt%curr==0) akt/=curr;
				add_ind(curr, i);
			}
		}
		
		cout<<curr_ans();
		
		for(int i=0;i<m;++i) {
			int a,b, akt;
			a=getint();
			b=getint();
			a--;
			
			akt=arr[a];
			while(akt>1) {
				int curr=pr[akt];
				while(akt%curr==0) akt/=curr;
				rem_ind(curr, a);
			}
			
			arr[a]=b;
			
			akt=arr[a];
			while(akt>1) {
				int curr=pr[akt];
				while(akt%curr==0) akt/=curr;
				add_ind(curr, a);
			}
			
			cout<<" "<<curr_ans();
		}
		ll szum=0;
		for(int i=0;i<n;++i) szum+=arr[i];
		cout<<" "<<szum<<"\n";
	}
	return 0;
}
