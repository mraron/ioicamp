#include<bits/stdc++.h>
using namespace std;

int main() {
	int cnt;
	cin>>cnt;
	vector<int> t(cnt);
	for(int i=0;i<cnt;++i) cin>>t[i];
	sort(t.begin(), t.end());
	cout<<cnt<<"\n";
	for(auto i:t) cout<<i<<" ";cout<<"\n";
	return 0;
}
