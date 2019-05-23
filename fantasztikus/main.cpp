#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=100001;
int tree[4*MAXN];
int lazy[4*MAXN];
void upd(int ind, int L, int R) {
	if(lazy[ind]>0) {
		tree[ind]=R-L+1;
	}else {
		if(L==R) {
			tree[ind]=0;
		}else {
			tree[ind]=tree[2*ind]+tree[2*ind+1];
		}
	}
}

void upd(int ind, int L, int R, int i, int j, int val) {
	if(j<L || R<i) return ;
	if(i<=L && R<=j) {
		lazy[ind]+=val;
		upd(ind, L, R);
		return ;
	}
	
	upd(2*ind, L, (L+R)/2, i, j, val);
	upd(2*ind+1, (L+R)/2+1, R, i, j, val);
	
	upd(ind, L, R);
}

int n,k,m;

int arr[MAXN];
vector<int> pr;
int lp[MAXN];
vector<int> fakt[MAXN];
set<int> prime[MAXN];

void add_inv(int ind, int pr) {
	//cerr<<"add_inv START "<<ind<<" "<<pr<<"\n";cerr.flush();
	auto it=prime[pr].insert(ind).first;
	if(it!=prime[pr].begin()) {
		int kezd=max(0,ind-k+1);
		int veg=min(*prev(it), n-k);
		if(kezd<=veg) {
			upd(1, 0, n-k, kezd, veg, 1);
		}
	}
	
	if(next(it)!=prime[pr].end()) {
		int kezd=max(0,*next(it)-k+1);
		int veg=min(ind,n-k);
		if(kezd<=veg) {
			upd(1, 0, n-k, kezd, veg, 1);
		}
	}
	
	if(it!=prime[pr].begin() && next(it)!=prime[pr].end()) {
		int kezd=max(0,*next(it)-k+1);
		int veg=min(*prev(it),n-k);
		if(kezd<=veg) {
			upd(1, 0, n-k, kezd, veg, -1);
		}
	}
	//cerr<<"add_inv VEG\n";cerr.flush();
}	

void rem_inv(int ind, int pr) {
	//cerr<<"rem_inv START "<<ind<<" "<<pr<<"\n";cerr.flush();
	auto it=prime[pr].lower_bound(ind);
	
	if(it!=prime[pr].begin()) {
		int kezd=max(0,ind-k+1);
		int veg=min(*prev(it), n-k);
		if(kezd<=veg) {
			upd(1, 0, n-k, kezd, veg, -1);
		}
	}
	assert(it!=prime[pr].end());
	if(next(it)!=prime[pr].end()) {
		int kezd=max(0,*next(it)-k+1);
		int veg=min(ind,n-k);
	
		if(kezd<=veg) {
			upd(1, 0, n-k, kezd, veg, -1);
		}
	}
	
	if(it!=prime[pr].begin() && next(it)!=prime[pr].end()) {
		int kezd=max(0,*next(it)-k+1);
		int veg=min(*prev(it),n-k);
		if(kezd<=veg) {
			upd(1, 0, n-k, kezd, veg, 1);
		}
	}

	prime[pr].erase(ind);
//	cerr<<"rem_inv VEG\n";cerr.flush();
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
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	for(int i=2;i<MAXN;++i) {
		if(lp[i]==0) {
			lp[i]=i;
			pr.push_back(i);
		}
		
		for(int j=0;j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<MAXN;++j) {
			lp[i*pr[j]]=pr[j];
		}
	}
	
	for(int i=1;i<MAXN;++i) {
		int curr=i;
		while(curr>1) {
			int akt=lp[curr];
			while(curr%akt==0) curr/=akt;
			fakt[i].push_back(akt);
		}	
	}
	
	int T=getint();
	while(T--) {
		n=getint();
		k=getint();
		m=getint();
	//	cerr<<n<<" "<<k<<" "<<m<<"hmhmhm\n";cerr.flush();
		for(int i=0;i<4*n;++i) tree[i]=lazy[i]=0;
		
		for(int i=0;i<n;++i) arr[i]=getint();
		//for(int i=0;i<n;++i) cerr<<arr[i]<<"\n";
		
		for(int i=0;i<n;++i) {
			for(auto j:fakt[arr[i]]) {
				add_inv(i, j);
			}
		}
		
		cout<<tree[1]<<" ";
		for(int i=0;i<m;++i) {
			int a,b;
			a=getint();
			//cerr<<a<<"asd\n";
			b=getint();
			a--;
			//cerr<<"Q"<<a<<" "<<b<<"Q\n";
			
			for(auto j:fakt[arr[a]]) {
				rem_inv(a, j);
			}
			
			arr[a]=b;
			
			for(auto j:fakt[arr[a]]) {
				add_inv(a, j);
			}
			
			cout<<tree[1]<<" ";
		}
		
		ll res=0;
		for(int i=0;i<n;++i) res+=arr[i];
		cout<<res<<"\n";
		
		
		for(int i=0;i<n;++i) {
			for(auto j:fakt[arr[i]]) {
				rem_inv(i, j);
			}
		}
	}
	return 0;
}	
