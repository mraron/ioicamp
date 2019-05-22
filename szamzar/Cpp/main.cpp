#include<bits/stdc++.h>
#include "zar.h"
using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)(x).size()
#define xx first
#define yy second
void csinal(string x) {
	for(auto i:x) be(i);
}
#pragma GCC optimize("Ofast")
#pragma GCC target("sse2,sse3,ssse3,sse4,avx2,tune=native")
int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	
	string pwd=jelszo();
	
	vector<string> pre, suf;
	pre.push_back("");
	suf.push_back("");
	for(int i=0;i<(int)pwd.size();++i) {
		pre.push_back(pwd.substr(0, i+1));
		suf.push_back(pwd.substr(pwd.size()-1-i, i+1));
	}
	
	//for(auto i:pre) cerr<<i<<"\n";
	//for(auto i:suf) cerr<<i<<"\n";
	
	for(auto i:pre) {
		for(char c='0';c<='9';++c) {
			for(auto j:suf) {
				resetA();
				csinal(i);
				be(c);
				csinal(j);
				if(nyito()) {
					string val=i+string(1,c)+j;
					if(val!=pwd) {
						nyit(val);
						return 0;
					}
				}
			}
		}
	}
	/*
	for(auto i:pre) {
		resetA();
		
		if(sz(i)<sz(pwd)) {
			
			be(pwd[sz(i)]);
			csinal(i);
		}
	}*/
	
	nyit(pwd);
	return 0;
}
