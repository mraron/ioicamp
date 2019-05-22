#include<bits/stdc++.h>
#include "query.h"
using namespace std;
int n, both;
vector<int> lst[15];
int main() {
	n=Size();both=0;
	for(int i=1;i<=n;++i) {
		lst[0].push_back(i);
	}
	while(1) {
		for(int i=0;i<15;++i) {
			if(lst[i].size()>0 && (1<<i)+both>n/2) {
				Answer(lst[i][0]);
				return 0;
			}
			if(lst[i].size()>1) {
				if(Member(lst[i][lst[i].size()-2], lst[i].back())) {
					lst[i+1].push_back(lst[i].back());
					lst[i].pop_back();
					lst[i].pop_back();
				}else {
					both+=1<<i;
					lst[i].pop_back();
					lst[i].pop_back();
				}
			}
		}
	}
	return 0;
}
