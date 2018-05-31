/*
ID: noszaly1
TASK: {TASK}
LANG: C++11               
*/

//Noszály Áron 10o Debreceni Fazekas Mihály Gimnázium

#include "rendminta.h"
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
#define gc getchar
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


struct Treap {
	int key, pri;
	int sz;
	int sum;
	
	Treap *L,*R;
	
	Treap() {}
	
	Treap(int item) : L(NULL), R(NULL) {
		key=item;
		pri=rand();
	}
};

typedef Treap * pTreap;

void update(pTreap& root) {
	if(root==NULL) return ;
	
	root->sz=(root->L==NULL?0:root->L->sz)+(root->R==NULL?0:root->R->sz)+1;
}

void split(pTreap root, int key, pTreap& L, pTreap& R) {
	if(root==NULL) {
		L=NULL;
		R=NULL;
	}else if(key < root->key) {
		split(root->L, key, L, root->L);
		R=root;
	}else {
		split(root->R, key, root->R, R);
		L=root;	
	}
	
	update(root);
}

void insert(pTreap& root, pTreap item) {
	if(root==NULL) {
		root=item;
	}else if(root->pri < item->pri) {
		split(root, item->key, item->L, item->R);
		root=item;
	}else {
		insert(item->key < root->key ? root->L : root->R, item);
	}
	
	update(root);
}

void merge(pTreap& root, pTreap L, pTreap R) {
	if(L==NULL || R==NULL) {
		root=(L!=NULL?L:R);
	}else if(L->pri < R->pri) {
		merge(R->L, L, R->L);
		root=R;
	}else {
		merge(L->R, L->R, R);
		root=L;
	}
	
	update(root);
}

void erase(pTreap& root, int key) {
	if(root->key == key) {
		merge(root, root->L, root->R);
	}else {
		erase(key< root->key ? root->L : root->R, key);
	}
	
	update(root);
}

int meret(pTreap root) {
	if(root==NULL) return 0;
	return root->sz;
}

pTreap kthquery(pTreap& root, int k) {
	if(meret(root->L)==k-1) return root;
	else if(meret(root->L)<k-1) return kthquery(root->R, k-meret(root->L)-1);
	return kthquery(root->L, k);
}

void thquery(pTreap& root, int key, int& ans, bool& found) {
	if(root->key<=key) {
		ans+=meret(root->L)+1;
	}
	if(root->key>key) thquery(root->L, key, ans, found);
	else if(root->key<key) {
		thquery(root->R, key, ans, found);
	}else {
		found=true;
		return ;
	}
}

bool benne(pTreap& root, int key) {
	if(root==NULL) return false;
	
	if(key<root->key) {
		return benne(root->L, key);
	}else if(key>root->key) {
		return benne(root->R, key);
	}
	
	return true;
}

void print(pTreap root) {
	if(root==NULL) return ;
	print(root->L);
	cout<<root->key<<" ";
	print(root->R);
}

pTreap root=NULL;

void Adat(int x) {
	//print(root);
	//cerr<<"Adat: "<<x<<"\n";
	if(!benne(root, x))
		insert(root, new Treap(x));
}

int Elemszam() {
	//print(root);
	//cerr<<"Size query\n";
	return (root==NULL?0:root->sz);
}

int Kadik(int k) {
	//print(root);
	//cerr<<"Kth query: "<<k<<"\n";
	return kthquery(root, k)->key;
}

int Hanyadik(int k) {
	//print(root);
	//cerr<<"Hanyadik: "<<k<<"\n";
	int ans=0;
	bool found=false;
	thquery(root, k, ans,found);
	//cerr<<ans<<" "<<found<<"\n";
	return (found?ans:0);
}

void KTorol(int k) {
	erase(root, Kadik(k));
}

void Torol(int x) {
	erase(root, x);
}
