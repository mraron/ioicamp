#include <bits/stdc++.h>

using namespace std;
#define gc getchar_unlocked



typedef long long ll;



const ll mod = (int)1e9+7;

ll fact[6000301], inv[3001010], invfact[3001100];
ll dp[3000501];


int select(vector<int>& t) {
	int mi=t[0];
	int mx=t[0];
	
	for(int i=1;i<t.size();++i) {
		if(t[i]<mi) {
			mi=t[i];
		}else if(t[i]>mx) {
			mx=t[i];
		}else {
			return i-2;
		}
	}
	
	return t.size()-1;
}

void init() {

    fact[0]=1;

    for(int i=1;i<=6000100;++i) fact[i]=(fact[i-1]*i)%mod;

    

    inv[0]=1;

    inv[1]=1;

    for(int i=2;i<=3000100;++i) {

        inv[i]=(-(mod/i)*inv[mod%i]-mod)%mod+mod;

    }

    

    invfact[0]=1;

    for(int i=1;i<=3000100;++i) {

        invfact[i]=(inv[i]*invfact[i-1])%mod;

    }  
	
	
	dp[0]=1;
	dp[1]=1;
	
	for(int i=1;i<=3000100;++i) {
		dp[i]=(((((fact[2*i]*invfact[i])%mod)*invfact[i])%mod)*inv[i+1])%mod;
	}
}




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
   
    init();

    int T;

    T=getint<int>();


    while(T-- ){

        int n,k;

		n=getint<int>();
		k=getint<int>();
		
		if(k==0) {
			printf("%d\n", (int)dp[n]);
			continue ;
		}
        

        vector<int> t(k);

        for(int i=0;i<k;++i) {
			t[i]=getint<int>();
   
        }

		

   
	
		int prefix=select(t);
        reverse(t.begin(), t.end());
        int suffix=select(t);
        if(prefix+suffix<k-1) {
			printf("0\n");
			continue ;
		}

        ll ans=prefix+suffix-k+2;
        
        ll kulon=1;
		ll minusz=0;

        sort(t.begin(), t.end());
		//for(auto i:t) cerr<<i<<" ";cerr<<"\n";
        for(int i=1;i<k;++i) {

			minusz+=t[i]-t[i-1]-1;
			//cerr<<min(t[i],t[i-1])<<" "<<max(t[i],t[i-1])<<" "<<(nincs[max(t[i],t[i-1])]-nincs[min(t[i],t[i-1])])<<"?!??\n";
            kulon*=dp[t[i]-t[i-1]-1];

    

            kulon%=mod;

        }

    
		//cerr<<kulon<<" "<<ans<<" "<<minusz<<"\n";
        kulon*=dp[(n-k)-minusz+1];
        //cerr<<ans<<"ANS\n";
        //cerr<<kulon<<"WTFWETFQ\n";
		//cerr<<nincs[n]-minusz+1<<"!!\n";
        kulon%=mod;

		
		printf("%d\n", (int)((ans*kulon)%mod));
       
		
		
    }

    

    return 0;

}
