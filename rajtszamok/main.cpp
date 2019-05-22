#include<bits/stdc++.h>
#include "valasz.h"
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n=induloszam();
	vector<int> van(n+1,1);
	int eddig=0;
	for(int i=0;i<=10;++i) {
		vector<int> van_null, van_egy;
		int kell_null=0, kell_egy=0;
		for(int j=1;j<=n;++j) {
			bool ok=true;
			for(int k=0;k<i;++k) {
				int egyik=((1<<k)&j)!=0;
				int masik=((1<<k)&eddig)!=0;
				ok&=egyik==masik;
			}
			if(ok) {
				if(j&(1<<i)) kell_egy++;
				else kell_null++;
			}
		}
		
		for(int j=1;j<n;++j) {
			if(van[j]) {
				if(kerdes(j,i)) van_egy.push_back(j);
				else van_null.push_back(j);
			}
		}
		//cerr<<kell_null<<" "<<kell_egy<<" - "<<van_null.size()<<" "<<van_egy.size()<<"\n";
		if(kell_null!=van_null.size()) {
			eddig|=0;
			for(auto i:van_egy) van[i]=0;
		}else {
			eddig|=1<<i;
			for(auto i:van_null) van[i]=0;
		}
	}
	//cerr<<eddig<<"\n";
	megoldas(eddig);
	return 0;
}
