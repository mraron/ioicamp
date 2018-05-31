/*
ID: noszaly1
TASK: {TASK}
LANG: C++11               
*/

//Noszály Áron 10o Debreceni Fazekas Mihály Gimnázium

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<cassert>
#include<cassert>
#include<unordered_map>
#include<unordered_set>
#include<functional>
#include<queue>
#include<stack>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<sstream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<numeric>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define xx first
#define yy second
#define sz(x) (int)(x).size()
#define gc getchar_unlocked
#define IO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const double PI=acos(-1);

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

int n,k;

int sub[800001][26];
int sz[800001];
bool vege[800001];
int ans[800001];

int nxt=1;

int buf[32];
int ind=0;


void insert() {
	int root=0;
	int cans=0;
	int i=0;
	for(;i<ind;) {
		//cerr<<*i;
		if(!sub[root][buf[i]]){
			sub[root][buf[i]]=nxt++;
		}
		
		
		cans+=++sz[root];
		root=sub[root][buf[i]];
		i++;
	}
	
	
	cans+=++sz[root];
	ans[root]=cans;
	//cerr<<cans<<"\n";
	vege[root]=1;
}

int query() {
	int root=0;
	int cans=0;
	int i=0;
	for(;i<ind;) {
		cans+=sz[root];
		if(!sub[root][buf[i]]){
			return cans;
		}	
		
		root=sub[root][buf[i]];
		i++;
	}

	cans+=sz[root];
	
	if(vege[root]) return ans[root];

	return cans;
}


void readStr(int buf[]) {
	char c;
	while((c=gc()) && c!=EOF && !(c>='a' && c<='z'));
	ind=0;
	do {
		buf[ind++]=c-'a';
	}while((c=gc()) && c!=EOF && (c>='a' && c<='z'));
	
}

int main() {
	n=getint<int>();
	for(int i=0;i<n;++i) {
		readStr(buf);
		insert();
	}
	
	k=getint<int>();
	for(int i=0;i<k;++i) {
		readStr(buf);
		printf("%d\n", query());
	}
	
	
	return 0;
}

