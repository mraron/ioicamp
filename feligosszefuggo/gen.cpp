#include<bits/stdc++.h>
using namespace std;
int main() {
	srand(time(0));
	int m;
	cout<<"1\n";
	cout<<"10 "<<(m=rand()%20)<<"\n";
	for(int i=0;i<m;++i) {
		int a=rand()%10+1;
		int b=rand()%10+1;
		cout<<a<<" "<<b<<"\n";
	}
}
