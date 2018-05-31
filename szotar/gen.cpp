#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int main() {
	int t=time(0);
	srand(t);
	cerr<<t<<"\n";
	cout<<"10000\n";
	for(int i=0;i<10000;++i) {
		string t;
		int len=rand()%20+5;
		for(int j=0;j<len;++j) {
			t.pb(rand()%26+'a');
		}
		
		cout<<t<<"\n";
	}
	
	cout<<"10000\n";
	for(int i=0;i<10000;++i) {
		string t;
		int len=rand()%20+5;
		for(int j=0;j<len;++j) {
			t.pb(rand()%26+'a');
		}
		
		cout<<t<<"\n";
	}
}
