#include<bits/stdc++.h>
#include "query.h"

using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second
int main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n=Size();
	
	int sz1=1, szmasik, masik=-1;
	for(int i=2;i<=n;++i) {
		if(Member(1, i)==1) {
			sz1++;
			if(sz1>n/2) {
				Answer(1);
				return 0;
			}
		}else {
			if(masik==-1) {
				masik=i;
				szmasik=1;
			}else {
				szmasik++;
			}
		}
		int hatra=n-i;
		if(masik!=-1 && hatra+szmasik<sz1) {
			Answer(1);
		}
		if(masik!=-1 && hatra+sz1<szmasik) {
			Answer(masik);
		}
	}
	
	return 0;
}
