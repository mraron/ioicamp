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
#define FORN(i, n) for(int i=0;i<(n);i++)
#define gc getchar
#define IO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)

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


//felul[T][k] = SZUMMA l=0..k dp[TB][k-l] * dp[TJ][l] 
//dp[T][k] = SZUMMA l=0..k felul[T][l] * (szélesség-l choose k-l) * magasság! / (magasság-L)!

#define int ll

vector<int> t;
int n;
int k;


ll mod=1e9+7;

ll fastpow(ll a, ll b) {
	if(b==0) return 1;
	ll fele=fastpow(a,b/2);
	ll ans=(fele*fele)%mod;
	if(b&1) ans=(ans*a)%mod;
	return ans;
}


ll mulm(ll x, ll y) {
	return (x*y)%mod;
}

ll dp[1000001];
void init() {
	dp[0]=1;
	for(int i=1;i<=1000000;++i) {
		dp[i]=mulm(dp[i-1],i);
	}
}
ll fact(ll x) {
	return dp[x];
}

ll divm(ll x, ll y) {
	return (x*fastpow(y,mod-2))%mod;
}

ll choose(ll a, ll b) {
	
	return divm(fact(a), mulm(fact(b), fact(a-b)));
}


struct state {
	int l,r,h;
	
	vector<ll> felul;
	vector<ll> dp;
	void calc() {
		dp.resize(k+1, 0);
		felul.resize(k+1, 0);
		
		dp[0]=1;
		felul[0]=1;

		if(r<l) {
			return ;
		}
		

		
		int n=r-l+1;
		vector<int> arr(n);
		for(int i=l;i<=r;++i) {
			arr[i-l]=t[i];
		}

		auto lowest=min_element(all(arr));
		
		int H=*lowest-h;
//cerr<<H<<"\n";
		
		state L, R;
		L.l=l, L.r=lowest-arr.begin()+l-1;L.h=*lowest;
		R.l=lowest-arr.begin()+l+1, R.r=r;R.h=*lowest;
		
		L.calc();
		R.calc();
		
		for(int i=1;i<=k;++i) {
			for(int j=0;j<=i;++j) {
				felul[i]=(felul[i]+mulm(L.dp[i-j],R.dp[j]))%mod;
			}
		}
		
		
		for(int i=1;i<=min(k,n);++i) {
			for(int j=0;j<=i;++j) {
				//cerr<<i<<" "<<j<<" "<<min(H,n)<<"\n";
				//if(n-j<i-j || H-j<0) continue ;	
				if(n-j<0) break ;
				if(i-j<0) break ;
				if(H+j<i) continue ;
				if(min(H,n)<i-j) continue ;
	
				ll ans=divm(mulm(mulm(felul[j], choose(n-j, i-j)),fact(H)), fact(H-(i-j)));
				//cerr<<i<<" "<<j<<" JJJ -> "<<ans<<" "<<n-j<<" "<<H<<"\n";
				dp[i]=(dp[i]+ans)%mod;
			}
		}
		/*cerr<<l<<" "<<r<<" "<<h<<" "<<H<<"\n";
		for(auto i:felul) cerr<<i<<" ";
		cerr<<"felul\n";
		for(auto i:dp) cerr<<i<<" ";
		cerr<<"dp\n";*/
	}
};

main() {
	IO;
	init();
	cin>>n>>k;
	t=vector<int>(n);
	for(int i=0;i<n;++i) cin>>t[i];
	state ans;
	ans.l=0, ans.r=n-1, ans.h=0;
	
	ans.calc();
	cout<<ans.dp[k]<<"\n";
	return 0;
}

