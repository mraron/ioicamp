#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include "grundy.h"

using namespace std;


vector<int> dp;
vector<int> lepes;

int main() {
	int n;
	cin>>n;
	
	dp.resize(n+1);
	
	dp[1]=0;
	dp[2]=0;
	for(int i=3;i<=n;++i) {
		set<int> kisebb;
		for(int j=1;j<i && j!=i-j;++j) {
			kisebb.insert(dp[j]^dp[i-j]);
		}
		int j=0;
		for(;kisebb.find(j)!=kisebb.end();j++){}
		dp[i]=j;
	}
	
	for(int i=1;i<=n;++i) cout<<dp[i]<<",";
	cout<<"\n";
}
