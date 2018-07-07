#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
main() {
    int n;
    cin>>n;
    vector<int> t(n);
    for(int i=0;i<n;++i) {
		cin>>t[i];
    }
	vector<int> mx(n);
	mx[0]=1;
	vector<bool> fontos(n);
	for(int i=1;i<n;++i) {
		mx[i]=max(t[i], mx[i-1]);
		fontos[i]=(mx[i]>mx[i-1]);
	}
	
	vector<int> dp[2];
	dp[0]=vector<int>(10021);
	dp[1]=vector<int>(10021);
	
	for(int i=0;i<=n;++i) {
		dp[(n-1)&1][i]=1;
	}
	
	int ans=t[n-1]-1;
	int mod=1e6+7;
	for(int i=n-2;i>=0;i--) {
		for(int j=0;j<=n;++j) {
			dp[i&1][j]=(dp[(i&1)^1][j]*j+dp[(i&1)^1][j+1])%mod;
		}
	
		if(fontos[i]) {
			ans=(ans+(t[i]-1)*dp[i&1][mx[i]-1])%mod;
		}else {
			ans=(ans+(t[i]-1)*dp[i&1][mx[i]])%mod;
		}
		
		
		//cerr<<mx[i]<<" "<<dp[i&1][mx[i]]<<"\n";
		//ans=(ans+dp[i&1][mx[i]])%mod;
	}
	
	cout<<ans+1<<"\n";
    return 0;
}
